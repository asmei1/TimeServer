#include "Helper.hpp"
#include <winsock2.h>
#include "InetAddress.h"
#include "cpptinytools/StringTools.hpp"

bool anl::validateIP(const std::string& ip)
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

void anl::getLocalInterface(in_addr& localInterface)
{
   char myname[32] = { 0 };
   gethostname(myname, 32);
   //dont free this memory, it has be done by system
   hostent* he = gethostbyname(myname);
   memcpy(&localInterface.s_addr, *he->h_addr_list, 4);
}

std::string anl::hostNameToIP(const std::string& hostName)
{
   hostent* he = gethostbyname(hostName.c_str());
   std::string ip;

   if(nullptr == he)
   {
      //gethostbyname failed
      throw WSAGetLastError();
   }
   in_addr** addr_list;
   //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
   addr_list = reinterpret_cast<in_addr**>(he);

   if(addr_list[0] != nullptr)
   {
      //Return the first one;
      ip = inet_ntoa(*addr_list[0]);
   }
   return ip;
}

std::optional<std::string> anl::parseAddress(const std::string& hostName)
{
   std::string ip = hostName;

   if(false == validateIP(hostName))
   {
      if(hostName == "localhost")
      {
         ip = "127.0.0.1";
      }
      else
      {
         try
         {
            ip = hostNameToIP(hostName);
         }
         catch(...)
         {
            return std::nullopt;
         }
      }
   }
   return ip;
}

std::string anl::socketAddr2String(const sockaddr_in& addr)
{
   return inet_ntoa(addr.sin_addr) + std::string(":") + std::to_string(addr.sin_port);
}

std::string anl::socketAddr2String(const InetAddress& addr)
{
   return inet_ntoa(addr.getRawSettings().sin_addr) + std::string(":") + std::to_string(addr.getRawSettings().sin_port);
}
