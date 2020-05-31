#pragma once
#include "NetworkHeaders.hpp"
#include "Helper.hpp"

namespace anl
{
   class InetAddress
   {
      InetAddress() = default;
   public:
      InetAddress(const std::string& hostName, const int& portNumber)
      {
         const auto& ipOpt = parseAddress(hostName);

         this->addr.sin_family = AF_INET;
         this->addr.sin_port = htons(portNumber);
         inet_pton(AF_INET, ipOpt->c_str(), &addr);
      }

      InetAddress(const sockaddr_in& addrr)
      {
         this->addr = addrr;
      }

      sockaddr_in getRawSettings() const
      {
         return this->addr;
      }

      sockaddr* toSockAddr() const
      {
         return (sockaddr*)&addr;
      }

      int getStructSize() const
      {
         return sizeof(addr);
      }

      static InetAddress broadcastAddress(int port)
      {
         InetAddress inet{};

         inet.addr.sin_family = AF_INET;
         inet.addr.sin_port = htons(port);
         inet_pton(AF_INET, "255.255.255.255", &inet.addr);

         return inet;
      }

      std::string toString()
      {
         return inet_ntoa(addr.sin_addr) + std::string(":") + std::to_string(addr.sin_port);
      }

   private:
      sockaddr_in addr;

   };
}
