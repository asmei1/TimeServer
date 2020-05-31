#pragma once
#include <cpptinytools/StringTools.hpp>
#include <iostream>
#include <algorithm>
#include <functional>

int main()
{
   for (auto && token : ctt::Parser::split("Some text", " "))
   {
      std::cout << token << std::endl;
   }

   auto print = [](const auto& p) {std::cout << p; };
   auto&& tokens = ctt::Parser::split("Some text", " ");
   std::for_each(tokens.cbegin(), tokens.cend(), print);
   return 0;
}
