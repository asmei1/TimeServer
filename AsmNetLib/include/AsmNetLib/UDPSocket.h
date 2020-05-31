#pragma once
#include <winsock2.h>
#include <string>
#include <vector>
#include <functional>
#include <optional>
#include "Types.h"
#include <stdexcept>

namespace anl
{
   class InetAddress;

   class UDPSocket
   {
      friend class UDPServerSocket;
   public:
      UDPSocket(ILogger* logger);
      UDPSocket(ILogger* logger, uint16_t portNumber, bool enableBroadcast = false);

      ~UDPSocket();


      void closeSocket();
      void sendData(const Data& data, const InetAddress& addrr) const;
      void recvData(Data& data, const InetAddress& addrr, long timeoutUSec = -1) const;
      InetAddress recvData(Data& data) const;
      sockaddr_in getRawSettings() const;

   private:
      void enableBroadcast();
      ILogger* logger;
      sockaddr_in addrr;
      SOCKET socketHandler;
   };

}
