#include "SocketDescription.hpp"


#include "BindException.hpp"
#include "SocketException.hpp"
#include "TimeoutException.hpp"
#include "InetAddress.hpp"

auto inetAddrToInternalStruct(const anl::InetAddress& addr)
{
   sockaddr_in rV;
   memset(static_cast<void*>(&rV), 0, sizeof(sockaddr_in));
   rV.sin_family = AF_INET;
   rV.sin_addr.S_un.S_addr = htonl(addr.getAddress().toUint64());
   rV.sin_port = htons(addr.getPort());
   return rV;
}


anl::SocketDescription::SocketDescription(SocketType socketType, IPPROTO protocol)
{
   int type = 0;
   switch(socketType)
   {
      case SocketType::TCP:
         type = SOCK_STREAM;
         break;
      case SocketType::UDP:
         type = SOCK_DGRAM;
         break;
      case SocketType::RAW:
         type = SOCK_RAW;
         break;
      default:;
   }
   this->socketHandler = ::socket(AF_INET, type, protocol);

   if(INVALID_SOCKET == this->socketHandler)
   {
      throw SocketException(WSAGetLastError());
   }
}


void anl::SocketDescription::enableBroadcast()
{
   char broadcast = 1;
   if(setsockopt(this->socketHandler, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
   {
      closeSocket();
      throw SocketException(WSAGetLastError());
   }
   reusePort();
}

void anl::SocketDescription::bind(const InetAddress& addr)
{
   this->addr = inetAddrToInternalStruct(addr);

   if(SOCKET_ERROR == ::bind(this->socketHandler, (sockaddr*)&this->addr, sizeof(this->addr)))
   {
      throw BindException(WSAGetLastError());
   }
}

void anl::SocketDescription::closeSocket()
{
   closesocket(this->socketHandler);
   this->socketHandler = INVALID_SOCKET;
}

anl::InetAddress anl::SocketDescription::toInetAddress() const
{
   return InetAddress{ Ip4Addr::fromULong(htonl(this->addr.sin_addr.S_un.S_addr)), htons(this->addr.sin_port) };
}

void anl::SocketDescription::sendDatagramTo(const Data& data, const InetAddress& addr) const
{
   auto internalAddr = inetAddrToInternalStruct(addr);
   int structSize = sizeof(internalAddr);
   if(SOCKET_ERROR == sendto(this->socketHandler, data.data(), static_cast<int>(data.size()), 0, reinterpret_cast<sockaddr*>(&internalAddr), structSize))
   {
      throw SocketException(WSAGetLastError());
   }
}

bool anl::SocketDescription::isCreated() const
{
   return this->socketHandler != SOCKET_ERROR || this->socketHandler != INVALID_SOCKET;
}

void anl::SocketDescription::recvDatagramFrom(Data& data, const InetAddress& addr, long timeoutUSec) const
{
   if(data.size() == 0)
   {
      data.resize(MAX_DATAGRAM_SIZE);
   }

   if(timeoutUSec != -1)
   {
      fd_set fds;
      int n;
      struct timeval tv;

      // Set up the file descriptor set.
      FD_ZERO(&fds);
      FD_SET(this->socketHandler, &fds);

      // Set up the struct timeval for the timeout.
      tv.tv_sec = 0;
      tv.tv_usec = timeoutUSec;

      // Wait until timeout or data received.
      n = select(this->socketHandler, &fds, nullptr, nullptr, &tv);
      if(n == 0)
      {
         throw TimeoutException{};
      }

      if(n == -1)
      {
         throw SocketException(WSAGetLastError());
      }
   }

   auto senderAddress = inetAddrToInternalStruct(addr);
   int senderAddressSize = sizeof(senderAddress);

   if(SOCKET_ERROR == recvfrom(this->socketHandler, data.data(), static_cast<int>(data.size()), 0, reinterpret_cast<sockaddr*>(&senderAddress), &senderAddressSize))
   {
      throw SocketException(WSAGetLastError());
   }
}

anl::InetAddress anl::SocketDescription::recvAnyDatagram(Data& data) const
{
   if(data.size() == 0)
   {
      data.resize(MAX_DATAGRAM_SIZE);
   }
   sockaddr_in tempAddress;
   int size = sizeof(tempAddress);

   if(SOCKET_ERROR == recvfrom(this->socketHandler, data.data(), static_cast<int>(data.size()), 0, reinterpret_cast<sockaddr*>(&tempAddress), &size))
   {
      throw SocketException(WSAGetLastError());
   }


   return InetAddress(Ip4Addr::fromULong(htonl(tempAddress.sin_addr.S_un.S_addr)), htons(tempAddress.sin_port));
}

void anl::SocketDescription::recvDataFromStream(Data& data, long singlePacketBufferSize) const
{
   int receivedBytes;
   char* buff = new char[singlePacketBufferSize];
   do
   {
      receivedBytes = recv(this->socketHandler, buff, singlePacketBufferSize, 0);
      if(receivedBytes == SOCKET_ERROR || receivedBytes == 0)
      {
         delete[] buff;
         throw SocketException(-1);
      }
      data.insert(data.end(), buff, buff + receivedBytes);


   } while(receivedBytes >= singlePacketBufferSize);
   delete[] buff;
}

bool anl::SocketDescription::sendPacketData(const Data& data) const
{
   bool success = true;

   if(false == send(this->socketHandler, data.data(), data.size(), 0))
   {
      success = false;
   }

   return success;
}

void anl::SocketDescription::connectTo(const InetAddress& address)
{
   auto addrToConnect = inetAddrToInternalStruct(address);
   //int size = sizeof(decltype(addrToConnect));
   int size = sizeof(sockaddr_in);
   bool success = 0 <= connect(this->socketHandler, reinterpret_cast<sockaddr*>(&addrToConnect), size);

   if(false == success)
   {
      throw SocketException(WSAGetLastError());
   }
}

void anl::SocketDescription::listen() const
{
   ::listen(this->socketHandler, 0);
}

std::optional<anl::SocketDescription> anl::SocketDescription::accept() const
{
   sockaddr_in client;
   int size = sizeof(sockaddr_in);
   SOCKET newSocket = ::accept(this->socketHandler, reinterpret_cast<sockaddr*>(&client), &size);

   if(SOCKET_ERROR == newSocket)
   {
      return std::nullopt;
   }
   SocketDescription rV;
   rV.addr = client;
   rV.socketHandler = newSocket;
   return rV;
}

void anl::SocketDescription::ttlToOne() const
{
   int ttl = 1;
   if(setsockopt(this->socketHandler, IPPROTO_IP, IP_MULTICAST_TTL, reinterpret_cast<char*>(&ttl), sizeof(ttl)) < 0)
   {
      throw SocketException(WSAGetLastError());
   }
}

void anl::SocketDescription::reusePort() const
{
   char reuse = 1;
   if(setsockopt(this->socketHandler, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
   {
      throw SocketException(WSAGetLastError());
   }
}

void anl::SocketDescription::disableMulticastLoop() const
{
   char loop = 0;
   if(setsockopt(this->socketHandler, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0)
   {
      throw SocketException(WSAGetLastError());
   }
}

void anl::SocketDescription::setMulticastInterface()
{
   in_addr localInterface;
   localInterface.S_un.S_addr = this->addr.sin_addr.S_un.S_addr;
   //getLocalInterface(localInterface);
   if(setsockopt(this->socketHandler, IPPROTO_IP, IP_MULTICAST_IF, reinterpret_cast<char*>(&localInterface), sizeof(localInterface)) < 0)
   {
      throw SocketException(WSAGetLastError());
   }
}

void anl::SocketDescription::joinToGroup(const Ip4Addr& address)
{
   ip_mreq group;
   group.imr_multiaddr.s_addr = htonl(address.toUint64());
   group.imr_interface.s_addr = this->addr.sin_addr.s_addr;

   if(setsockopt(this->socketHandler, IPPROTO_IP, IP_ADD_MEMBERSHIP, reinterpret_cast<char*>(&group), sizeof(group)) < 0)
   {
      throw SocketException(WSAGetLastError());
   }
}
