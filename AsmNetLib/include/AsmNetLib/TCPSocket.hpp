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
      bool isConnected() const;

      bool sendData(const Data& data) const;
      std::optional<Data> recvData() const;

      /// <summary>
      /// Get socket address (address and port).
      /// TODO: For now, this function returns proper data only when socket was created from TCPServerSocket
      /// </summary>
      /// <returns>Object with address and port</returns>
      InetAddress getSocketAddress() const;

      std::optional<InetAddress> getConnectedAddress() const;

   private:
      SocketDescription socketDesc{ SocketDescription::SocketType::TCP, IPPROTO_TCP };
      std::optional<InetAddress> addrConnectedTo{std::nullopt};
   };

}
