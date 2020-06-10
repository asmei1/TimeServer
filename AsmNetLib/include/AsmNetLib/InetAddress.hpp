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

      //static InetAddress defaultAddress()
      //{
      //   InetAddress inet{};

      //   inet.addr.sin_family = AF_INET;
      //   // if the port is specified as zero, the service provider assigns a unique port to the application from the dynamic client port range. On Windows Vista and later, the dynamic client port range is a value between 49152 and 65535. This is a change from Windows Server 2003 and earlier where the dynamic client port range was a value between 1025 and 5000... The application can use getsockname after calling bind to learn the address and the port that has been assigned to the socket.
      //   inet.addr.sin_port = 0;
      //   inet.addr.sin_addr.S_un.S_addr = ADDR_ANY;

      //   return inet;
      //}

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
      uint16_t  port;
   };
}
