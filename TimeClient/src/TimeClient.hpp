#pragma once
#include "cpptinytools/ILogger.hpp"

class TimeClient
{
public:
   TimeClient(const ctt::log::ILogger& loggerRef);

   void run();

private:
   const ctt::log::ILogger& logger;
};
