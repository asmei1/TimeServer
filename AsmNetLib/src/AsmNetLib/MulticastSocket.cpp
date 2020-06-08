#include "MulticastSocket.hpp"
#include <cassert>
#include "Helper.hpp"
#include "InetAddress.hpp"
#include "Exceptions/DatagramSizeOutOfRangeException.hpp"

using namespace anl;


MulticastSocket::MulticastSocket(const InetAddress& address)
{
   this->socketDesc = SocketDescription(SocketDescription::SocketType::UDP, static_cast<IPPROTO>(0));

   this->socketDesc.ttlToOne();
   this->socketDesc.disableMulticastLoop();
   this->socketDesc.reusePort();

   this->socketDesc.setMulticastInterface();
}


void MulticastSocket::bind(const InetAddress& address)
{
   this->socketDesc.bind(address);
}

void MulticastSocket::sendData(const Data& data, const InetAddress& address) const
{
   if(data.size() > MAX_DATAGRAM_SIZE)
   {
      throw DatagramSizeOutOfRangeException{};
   }

   this->socketDesc.sendDatagramTo(data, address);
}

void MulticastSocket::recvData(Data& data) const
{
   this->socketDesc.recvDataFromStream(data, RECV_BUFFER_SIZE);
}

MulticastSocket::~MulticastSocket()
{
   closeSocket();
}

void MulticastSocket::closeSocket()
{
   this->socketDesc.closeSocket();
}

void MulticastSocket::joinToGroup(const InetAddress& address)
{
   this->socketDesc.joinToGroup(address);
}

void MulticastSocket::leftFromGroup(const InetAddress& address)
{
   assert(false && "To implement");
}