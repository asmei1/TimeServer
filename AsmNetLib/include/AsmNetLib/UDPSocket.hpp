#pragma once
#include <vector>
#include "NetworkHeaders.hpp"
#include "SocketDescription.hpp"

namespace anl
{
   class UDPSocket 
   {
   public:
      UDPSocket();
      UDPSocket(const InetAddress& address);
      static UDPSocket broadcastSocket(const InetAddress& address);

      ~UDPSocket();

      void closeSocket();

      void sendData(const Data& data, const InetAddress& addr) const;
      void recvDataFrom(Data& data, const InetAddress& addrr, long timeoutUSec = -1) const;

      InetAddress recvData(Data& data) const;

   private:
      SocketDescription socketDesc{ SocketDescription::SocketType::UDP, IPPROTO_UDP };
   };

}
