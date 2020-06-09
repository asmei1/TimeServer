#include "TCPSocket.hpp"
#include "InetAddress.hpp"

using namespace anl;

TCPSocket::TCPSocket(const SocketDescription& socketDescription)
{
   this->socketDesc = socketDescription;
}

TCPSocket::TCPSocket()
{
   if(true == socketDesc.isCreated())
   {
      closeSocket();
   }
}

void TCPSocket::connectTo(const InetAddress& address)
{
   this->socketDesc.connectTo(address);
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

TCPSocket::~TCPSocket()
{
   this->closeSocket();
}
