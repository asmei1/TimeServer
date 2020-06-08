#pragma once
#include <string>
#include <optional>

#include "NetworkHeaders.hpp"

namespace anl
{
   void getLocalInterface(in_addr& localInterface);

   std::string hostNameToIP(const std::string& hostName);
   std::optional<std::string> parseAddress(const std::string& hostName);
}
