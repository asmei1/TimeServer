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
         this->addr.sin_port = (portNumber);
         this->addr.sin_addr.S_un.S_addr = inet_addr(ipOpt->c_str());
      }

      InetAddress(long address, short portNumber, int family = AF_INET)
      {
         this->addr.sin_family = family;
         this->addr.sin_port = (portNumber);
         this->addr.sin_addr.S_un.S_addr = address;
      }

      static InetAddress broadcastAddress(int port)
      {
         InetAddress inet{};

         inet.addr.sin_family = AF_INET;
         inet.addr.sin_port = (port);
         inet.addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");

         //inet_pton(AF_INET, "255.255.255.255", &inet.addr);

         return inet;
      }

      int getPort() const
      {
         return this->addr.sin_port;
      }

      long getAddress() const
      {
         return this->addr.sin_addr.S_un.S_addr;
      }

      std::string toString() const
      {
         return inet_ntoa(addr.sin_addr) + std::string(":") + std::to_string(addr.sin_port);
      }

      static bool isIPv4AddrValid(const std::string& ip)
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
