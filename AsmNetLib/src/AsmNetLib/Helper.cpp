#include "Helper.hpp"
#include <winsock2.h>
#include "InetAddress.hpp"
#include "cpptinytools/StringTools.hpp"

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

   if(false == InetAddress::isIPv4AddrValid(hostName))
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
