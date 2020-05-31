#pragma once
#include <optional>
#include <vector>

#include "NetworkHeaders.hpp"

namespace anl
{
   class InetAddress;

   class TCPSocket
   {
      friend class TCPServerSocket;
   public:
      TCPSocket(ILogger* logger);
      TCPSocket(ILogger* logger, SOCKET socketHandler, const sockaddr_in& addrr);

      ~TCPSocket();


      int initialize();
      void connectTo(const InetAddress& address);
      bool isConnected() const;
      void closeSocket();

      bool sendData(const Data& data) const;
      std::optional<Data> recvData() const;
      sockaddr_in getRawSettings() const;
   private:
      ILogger* logger;
      sockaddr_in addrr;
      SOCKET socketHandler;
      bool connected = false;
   };

}
