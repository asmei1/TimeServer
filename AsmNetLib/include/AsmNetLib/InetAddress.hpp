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
         this->addr.sin_addr.S_un.S_addr = inet_addr(ipOpt->c_str());
      }

      InetAddress(long address, short portNumber, int family = AF_INET)
      {
         this->addr.sin_family = family;
         this->addr.sin_port = htons(portNumber);
         this->addr.sin_addr.S_un.S_addr = address;
      }

      static InetAddress broadcastAddress(int port)
      {
         InetAddress inet{};

         inet.addr.sin_family = AF_INET;
         inet.addr.sin_port = htons(port);
         inet.addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");

         return inet;
      }
      
      static InetAddress defaultAddress()
      {
         InetAddress inet{};

         inet.addr.sin_family = AF_INET;
         // if the port is specified as zero, the service provider assigns a unique port to the application from the dynamic client port range. On Windows Vista and later, the dynamic client port range is a value between 49152 and 65535. This is a change from Windows Server 2003 and earlier where the dynamic client port range was a value between 1025 and 5000... The application can use getsockname after calling bind to learn the address and the port that has been assigned to the socket.
         inet.addr.sin_port = 0;
         inet.addr.sin_addr.S_un.S_addr = ADDR_ANY;

         return inet;
      }

      int getPort() const
      {
         return htons(this->addr.sin_port);
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
