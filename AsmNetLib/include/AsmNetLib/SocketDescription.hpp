#pragma once
#include <optional>

#include "NetworkHeaders.hpp"
#include "InetAddress.hpp"

namespace anl
{
   class SocketDescription
   {
   public:

      enum class SocketType
      {
         TCP = 1,
         UDP = 2,
         RAW = 3,
      };

      SocketDescription(SocketType socketType, IPPROTO protocol);

      void enableBroadcast();
      void bind(const InetAddress& addr);

      bool isCreated() const;
      void closeSocket();

      /// <summary>
      /// This function works properly only for SocketDescription object after bind function.
      /// TODO: It should works for sockets without bind too, but after send something
      /// </summary>
      /// <returns>InetAddress object with ipv4 address and port number</returns>
      InetAddress toInetAddress() const;

      //udp
      void sendDatagramTo(const Data& data, const InetAddress& addr) const;
      void recvDatagramFrom(Data& data, const InetAddress& addr, long timeoutUSec) const;
      InetAddress recvAnyDatagram(Data& data) const;

      //tcp
      void recvDataFromStream(Data& data, long singlePacketBufferSize) const;
      bool sendPacketData(const Data& data) const;
      void connectTo(const InetAddress& address);
      void listen() const;
      std::optional<SocketDescription> accept() const;

      //mutli
      void setMulticastInterface();
      void joinToGroup(const InetAddress& address);

      //options
      void ttlToOne() const;
      void reusePort() const;
      void disableMulticastLoop() const;

   private:
      SocketDescription() = default;

      sockaddr_in addr;
      SOCKET socketHandler = SOCKET_ERROR;
   };
}