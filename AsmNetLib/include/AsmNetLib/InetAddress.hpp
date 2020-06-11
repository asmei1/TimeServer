#pragma once
#include "cpptinytools/StringTools.hpp"
#include "Ip4Addr.hpp"

namespace anl
{
   /// <summary>
   /// For now, handle only IPv4 address
   /// </summary>
   class InetAddress
   {
   public:
      InetAddress(const char* hostname, uint16_t portNumber)
         : address(Ip4Addr::fromString(hostname).value())
      {
         this->port = portNumber;
      }

      InetAddress(const Ip4Addr& host, uint16_t portNumber)
         : address(host)
      {
         this->port = portNumber;
      }

      static InetAddress broadcastAddress(uint16_t port)
      {
         return InetAddress(Ip4Addr::fromString("255.255.255.255").value(), port);
      }

      int getPort() const
      {
         return this->port;
      }

      Ip4Addr getAddress() const
      {
         return this->address;
      }

      std::string toString() const
      {
         return this->address.toString() + std::string(":") + std::to_string(this->port);
      }

   private:
      Ip4Addr address;
      uint16_t port;
   };
}
