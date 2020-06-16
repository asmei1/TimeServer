#include "TCPSocket.hpp"
#include "InetAddress.hpp"

using namespace anl;

TCPSocket::TCPSocket(const SocketDescription& socketDescription)
{
   this->socketDesc = socketDescription;
}

TCPSocket::TCPSocket()
{
}

void TCPSocket::connectTo(const InetAddress& address)
{
   this->socketDesc.connectTo(address);
   this->addrConnectedTo = address;
}

bool TCPSocket::isConnected() const
{
   return this->getConnectedAddress().has_value();
}

void TCPSocket::closeSocket()
{
   this->socketDesc.closeSocket();
}

bool TCPSocket::sendData(const Data& data) const
{
   return this->socketDesc.sendPacketData(data);
}

std::optional<Data> TCPSocket::recvData() const
{
   try
   {
      Data recvData;
      this->socketDesc.recvDataFromStream(recvData, RECV_BUFFER_SIZE);
      return recvData;
   }catch(...)
   {
      return std::nullopt;
   }
}

InetAddress TCPSocket::getSocketAddress() const
{
   return this->socketDesc.toInetAddress();
}

std::optional<InetAddress> TCPSocket::getConnectedAddress() const
{
   return this->addrConnectedTo;
}

TCPSocket::~TCPSocket()
{
   this->closeSocket();
}
