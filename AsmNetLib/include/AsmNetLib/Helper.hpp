#pragma once
#include <string>
#include <optional>

#include "NetworkHeaders.hpp"

namespace anl
{
   void getLocalInterface(in_addr& localInterface);

   const char* hostNameToIP(const char* hostName);
   const char* parseAddress(const char* hostName);
}
