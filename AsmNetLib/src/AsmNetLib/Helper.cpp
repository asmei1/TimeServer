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

const char* anl::hostNameToIP(const char* hostName)
{
   hostent* he = gethostbyname(hostName);

   if(nullptr == he)
   {
      throw WSAGetLastError();
   }

   in_addr** addr_list;
   //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
   addr_list = reinterpret_cast<in_addr**>(he);

   if(addr_list[0] != nullptr)
   {
      //Return the first one;
      return inet_ntoa(*addr_list[0]);
   }
   return nullptr;
}

const char* anl::parseAddress(const char* hostName)
{
   if(false == Ip4Address::isAddressIsValid(hostName))
   {
      if(hostName == "localhost")
      {
         return "127.0.0.1";
      }
      else
      {
         try
         {
            return hostNameToIP(hostName);
         }
         catch(...)
         {
            return nullptr;
         }
      }
   }
   return hostName;
}
