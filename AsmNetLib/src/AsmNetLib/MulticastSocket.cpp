#include "MulticastSocket.hpp"
#include <cassert>
#include "InetAddress.hpp"
#include "Exceptions/DatagramSizeOutOfRangeException.hpp"

using namespace anl;


MulticastSocket::MulticastSocket(const InetAddress& address)
{
   this->socketDesc.ttlToOne();
   this->socketDesc.reusePort();

   this->bind(address);
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

InetAddress MulticastSocket::recvData(Data& data) const
{
   return this->socketDesc.recvAnyDatagram(data);
}

MulticastSocket::~MulticastSocket()
{
   if(true == socketDesc.isCreated())
   {
      closeSocket();
   }
}

void MulticastSocket::closeSocket()
{
   this->socketDesc.closeSocket();
}

void MulticastSocket::disableMulticastLoop() const
{
   this->socketDesc.disableMulticastLoop();
}

void MulticastSocket::joinToGroup(const Ip4Addr& address)
{
   this->socketDesc.joinToGroup(address);
}

void MulticastSocket::leftFromGroup(const Ip4Addr& address)
{
   assert(false && "To implement");
}