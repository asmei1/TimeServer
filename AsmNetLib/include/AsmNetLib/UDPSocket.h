#pragma once
#include <vector>
#include "NetworkHeaders.hpp"

namespace anl
{
   class InetAddress;

   class UDPSocket
   {
      friend class UDPServerSocket;
   public:
      UDPSocket();
      UDPSocket(uint16_t portNumber, bool enableBroadcast = false);

      ~UDPSocket();


      void closeSocket();
      void sendData(const Data& data, const InetAddress& addrr) const;
      void recvData(Data& data, const InetAddress& addrr, long timeoutUSec = -1) const;
      InetAddress recvData(Data& data) const;
      sockaddr_in getRawSettings() const;

   private:
      void enableBroadcast();
      sockaddr_in addrr;
      SOCKET socketHandler;
   };

}
