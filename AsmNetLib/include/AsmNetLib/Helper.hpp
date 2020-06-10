#pragma once
#include <string>
#include <optional>


#include "InetAddress.hpp"
#include "NetworkHeaders.hpp"

namespace anl
{

   std::vector<Ip4Address> getAllInterfaceAddresses();
   void getLocalInterface(in_addr& localInterface);

   const char* hostNameToIP(const char* hostName);
   const char* parseAddress(const char* hostName);
}
