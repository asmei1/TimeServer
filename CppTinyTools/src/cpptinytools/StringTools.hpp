#pragma once
#include <vector>
#include <string>

namespace ctt
{
   class StringTools
   {
   public:
      StringTools() = delete;
      StringTools(const StringTools& other) = delete;
      StringTools(StringTools&& other) noexcept = delete;
      StringTools& operator=(const StringTools& other) = delete;
      StringTools& operator=(StringTools&& other) noexcept = delete;


      static std::vector<std::string> split(const std::string& source, const std::string& delimiter);
      static bool replace(std::string& text, const std::string& from, const std::string& to);
      static bool isContainOnlyDigits(const std::string& str);

   };

}
