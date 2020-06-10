#pragma once
#include "NetworkHeaders.hpp"

#include <string>
#include <optional>

namespace anl
{
   class Ip4Address;
   std::vector<anl::Ip4Address> getAllInterfaceAddresses();
   void getLocalInterface(in_addr& localInterface);

   const char* hostNameToIP(const char* hostName);
   const char* parseAddress(const char* hostName);
}
