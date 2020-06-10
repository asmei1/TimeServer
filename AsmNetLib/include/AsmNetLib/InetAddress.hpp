#pragma once
#include <array>
#include "NetworkHeaders.hpp"
#include "Helper.hpp"
#include "cpptinytools/StringTools.hpp"

namespace anl
{
   class Ip4Address
   {
      Ip4Address() = default;
   public:
      using ipv4ad = std::array<uint8_t, 4>;


      ~Ip4Address() = default;
      Ip4Address(const Ip4Address& other) = default;
      Ip4Address(Ip4Address&& other) noexcept = default;
      Ip4Address& operator=(const Ip4Address& other) = default;
      Ip4Address& operator=(Ip4Address&& other) noexcept = default;

      static std::optional<Ip4Address> fromString(const char* ip)
      {
         if(false == isAddressIsValid(ip))
         {
            return std::nullopt;
         }


         std::vector<std::string> tokens = ctt::StringTools::split(parseAddress(ip), ".");
         Ip4Address rV;
         for(int i = 0; i < rV.a.size(); ++i)
         {
            rV.a[i] = std::stoi(tokens[i]);
         }

         return rV;
      }

      static Ip4Address fromULong(uint64_t address)
      {
         //todo add validation
         Ip4Address rV;
         rV.a[0] = static_cast<uint8_t>((address & 0xFF000000) >> 24 );
         rV.a[1] = static_cast<uint8_t>((address & 0x00FF0000) >> 16);
         rV.a[2] = static_cast<uint8_t>((address & 0x0000FF00) >> 8);
         rV.a[3] = static_cast<uint8_t>((address & 0x000000FF) >> 0);
         return rV;
      }

      static Ip4Address anyAddress()
      {
         Ip4Address rV;
         rV.any = true;
         return rV;
      }

      static bool isAddressIsValid(const char* ip)
      {
         // split the std::string into tokens
         std::vector<std::string> slist = ctt::StringTools::split(ip, ".");
         // if token size is not equal to four
         if(slist.size() != 4)
         {
            return false;
         }

         for(const auto& str : slist)
         {
            // check that std::string is number, positive, and range
            if(false == ctt::StringTools::isContainOnlyDigits(str) || std::stoi(str) < 0 || std::stoi(str) > 255)
            {
               return false;
            }
         }
         return true;
      }

      std::string toString() const
      {
         std::string rV;
         for(const auto& oc : a)
         {
            rV += std::to_string(oc);
            rV += ".";
         }
         rV.pop_back(); // to remove last dot
         return rV;
      }

      uint64_t toUint64() const
      {
         uint64_t rV;
         rV = this->a[0];
         rV = (rV << 8) + this->a[1];
         rV = (rV << 8) + this->a[2];
         rV = (rV << 8) + this->a[3];
         return rV;
      }

      bool isAnyAddress() const
      {
         return this->any;
      }

      ipv4ad a;
   private:
      bool any = false;
   };


   /// <summary>
   /// For now, handle only IPv4 address
   /// </summary>
   class InetAddress
   {
   public:
      InetAddress(const char* hostname, uint16_t portNumber)
         : address(Ip4Address::fromString(hostname).value())
      {
         this->port = portNumber;
      }

      InetAddress(const Ip4Address& host, uint16_t portNumber)
         : address(host)
      {
         this->port = portNumber;
      }

      static InetAddress broadcastAddress(uint16_t port)
      {
         return InetAddress(Ip4Address::fromString("255.255.255.255").value(), port);
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

      Ip4Address getAddress() const
      {
         return this->address;
      }

      std::string toString() const
      {
         return this->address.toString() + std::string(":") + std::to_string(this->port);
      }




   private:
      Ip4Address address;
      uint16_t  port;
   };
}
