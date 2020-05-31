#pragma once
#include "NetworkHeaders.hpp"
#include "Helper.hpp"
#include "cpptinytools/StringTools.hpp"

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


      static bool validateIPv4(const std::string& ip)
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


   private:
      sockaddr_in addr;

   };
}
