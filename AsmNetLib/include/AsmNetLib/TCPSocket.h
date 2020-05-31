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
      TCPSocket();
      TCPSocket(SOCKET socketHandler, const sockaddr_in& addrr);

      ~TCPSocket();


      int initialize();
      void connectTo(const InetAddress& address);
      bool isConnected() const;
      void closeSocket();

      bool sendData(const Data& data) const;
      std::optional<Data> recvData() const;
      sockaddr_in getRawSettings() const;

   private:
      sockaddr_in addrr;
      SOCKET socketHandler;
      bool connected = false;
   };

}
