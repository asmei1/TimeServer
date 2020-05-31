#include "StringTools.hpp"
#include <algorithm>

std::vector<std::string> ctt::StringTools::split(const std::string& source, const std::string& delimiter)
{
   std::vector<std::string> output;
   auto first = source.cbegin();

   while(first != source.cend())
   {
      auto second = std::find_first_of(first, source.cend(), delimiter.cbegin(), delimiter.cend());

      output.emplace_back(first, second);

      if(source.cend() == second)
      {
         break;
      }

      first = std::next(second);// +1;
   }

   return output;
}

bool ctt::StringTools::replace(std::string& text, const std::string& from, const std::string& to)
{
   size_t start_pos = text.find(from);
   if(start_pos == std::string::npos)
   {
      return false;
   }
   text.replace(start_pos, from.length(), to);
   return true;
}

bool ctt::StringTools::isContainOnlyDigits(const std::string& str)
{
   return (false == str.empty()) && (str.find_first_not_of("[0123456789]") == std::string::npos);
}
