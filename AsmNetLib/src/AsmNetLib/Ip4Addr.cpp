#include "Ip4Addr.hpp"
#include "Helper.hpp"
#include "cpptinytools/StringTools.hpp"

using namespace anl;

std::optional<Ip4Addr> Ip4Addr::fromString(const char* ip)
{
   if(false == isAddressIsValid(ip))
   {
      return std::nullopt;
   }


   std::vector<std::string> tokens = ctt::StringTools::split(parseAddress(ip), ".");
   Ip4Addr rV;
   rV.a[0] = std::stoi(tokens[0]);
   rV.a[1] = std::stoi(tokens[1]);
   rV.a[2] = std::stoi(tokens[2]);
   rV.a[3] = std::stoi(tokens[3]);

   return rV;
}

Ip4Addr Ip4Addr::fromULong(uint64_t address)
{
   //todo add validation
   Ip4Addr rV;
   rV.a[0] = static_cast<uint8_t>((address & 0xFF000000) >> 24);
   rV.a[1] = static_cast<uint8_t>((address & 0x00FF0000) >> 16);
   rV.a[2] = static_cast<uint8_t>((address & 0x0000FF00) >> 8);
   rV.a[3] = static_cast<uint8_t>((address & 0x000000FF) >> 0);
   return rV;
}

Ip4Addr Ip4Addr::any()
{
   Ip4Addr rV;
   rV.a = {};
   return rV;
}

bool Ip4Addr::isAddressIsValid(const char* ip)
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

std::string Ip4Addr::toString() const
{
   std::string rV;
   for(const auto& oc : a)
   {
      rV += std::to_string(oc);
      rV += ".";
   }
   rV.pop_back(); // to remove last dot
   return rV;
}

uint64_t Ip4Addr::toUint64() const
{
   uint64_t rV;
   rV = this->a[0];
   rV = (rV << 8) + this->a[1];
   rV = (rV << 8) + this->a[2];
   rV = (rV << 8) + this->a[3];
   return rV;
}
