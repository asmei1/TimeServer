#include "UDPSocket.hpp"
#include "Helper.hpp"
#include "InetAddress.hpp"
#include "Exceptions/DatagramSizeOutOfRangeException.hpp"

using namespace anl;

//TODO: think about it - without bind on socket, we cannot receive any message - (send will bind)

UDPSocket::UDPSocket()
{
   this->socketDesc.bind(InetAddress(Ip4Addr::any(), 0));
} 

UDPSocket::UDPSocket(const InetAddress& address)
{
   this->socketDesc.bind(address);
}

UDPSocket UDPSocket::broadcastSocket(const InetAddress& address)
{
   UDPSocket udp;
   udp.socketDesc.enableBroadcast();
   udp.socketDesc.bind(address);

   return udp;
}

void UDPSocket::closeSocket()
{
   if(true == this->socketDesc.isCreated())
   {
      this->socketDesc.closeSocket();
   }
}

void UDPSocket::sendData(const Data& data, const InetAddress& addr) const
{
   if(data.size() > MAX_DATAGRAM_SIZE)
   {
      throw DatagramSizeOutOfRangeException{};
   }

   this->socketDesc.sendDatagramTo(data, addr);
}

void UDPSocket::recvDataFrom(Data& data, const InetAddress& addr, long timeoutUSec) const
{
   if(data.size() > MAX_DATAGRAM_SIZE)
   {
      throw DatagramSizeOutOfRangeException{};
   }

   this->socketDesc.recvDatagramFrom(data, addr, timeoutUSec);
}

InetAddress UDPSocket::recvData(Data& data) const
{
   if(data.size() > MAX_DATAGRAM_SIZE)
   {
      throw DatagramSizeOutOfRangeException{};
   }

   return this->socketDesc.recvAnyDatagram(data);
}

UDPSocket::~UDPSocket()
{
   closeSocket();
}
