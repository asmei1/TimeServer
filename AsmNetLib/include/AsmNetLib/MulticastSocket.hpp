#pragma once

#include <vector>
#include "NetworkHeaders.hpp"
#include "SocketDescription.hpp"

namespace anl
{
   class MulticastSocket
   {
   public:
      MulticastSocket(const InetAddress& address);

      ~MulticastSocket();


      void closeSocket();

      void bind(const InetAddress& address);
      void sendData(const Data& data, const InetAddress& address) const;
      void recvData(Data& data) const;

      void joinToGroup(const InetAddress& address);
      void leftFromGroup(const InetAddress& address);
   private:
      SocketDescription socketDesc;
   };

}
