#include "TimeProtocol.hpp"

#include <string>

TimeProtocol::Command TimeProtocol::parseBuffer(const anl::Data& data)
{
   std::string command = std::string{ data.begin(), data.end() };
   command.erase(std::find(command.begin(), command.end(), '\0'), command.end());

   if(command == DISCOVERY_COMMAND_STR)
   {
      return Command::DISCOVERY;
   }


   return Command::INVALID;
}
