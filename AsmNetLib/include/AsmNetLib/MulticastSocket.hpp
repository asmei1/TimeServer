#pragma once

#include <vector>
#include "NetworkHeaders.hpp"
#include "SocketDescription.hpp"

namespace anl
{
   class MulticastSocket
   {
   public:
      MulticastSocket();
      MulticastSocket(const InetAddress& address);

      ~MulticastSocket();


      void closeSocket();

      void disableMulticastLoop() const;

      void bind(const InetAddress& address);
      void sendData(const Data& data, const InetAddress& address) const;
      InetAddress recvData(Data& data) const;

      void joinToGroup(const Ip4Addr& address);
      void leftFromGroup(const Ip4Addr& address);

      InetAddress getAddress() const
      {
         return this->socketDesc.toInetAddress();
      }
   private:
      SocketDescription socketDesc{ SocketDescription::SocketType::UDP, IPPROTO_UDP };
   };

}
