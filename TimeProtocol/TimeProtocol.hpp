#pragma once
#include "AsmNetLib/Types.hpp"

class TimeProtocol
{
public:
   TimeProtocol() = delete;
   TimeProtocol(const TimeProtocol& other) = delete;
   TimeProtocol(TimeProtocol&& other) noexcept = delete;
   TimeProtocol& operator=(const TimeProtocol& other) = delete;
   TimeProtocol& operator=(TimeProtocol&& other) noexcept = delete;

   enum Command
   {
      DISCOVERY,
      SEND_OFFER,  
      INVALID
   };


   static Command parseBuffer(const anl::Data& data);

   
   static inline const std::string DISCOVERY_COMMAND_STR = "DISCOVERY";
   static inline const anl::Data DISCOVERY_COMMAND = { DISCOVERY_COMMAND_STR.begin(), DISCOVERY_COMMAND_STR.end() };
};
