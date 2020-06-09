#pragma once
#include <optional>
#include <vector>

#include "NetworkHeaders.hpp"
#include "SocketDescription.hpp"

namespace anl
{
   class TCPSocket
   {
      friend class TCPServerSocket;
      TCPSocket(const SocketDescription& socketDescription);
   public:
      TCPSocket();
      ~TCPSocket();

      void closeSocket();

      void connectTo(const InetAddress& address);
      //bool isConnected() const;

      bool sendData(const Data& data) const;
      std::optional<Data> recvData() const;

   private:
      SocketDescription socketDesc{ SocketDescription::SocketType::TCP, IPPROTO_TCP };
   };

}
