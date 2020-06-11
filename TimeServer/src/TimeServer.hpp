#pragma once
#include <vector>

#include "ClientListenerService.hpp"
#include "cpptinytools/ILogger.hpp"

class TimeServer
{
public:
   TimeServer(const ctt::log::ILogger& logger);

   void initialize();
   void printInfo() const;
   void run();

private:
   const ctt::log::ILogger& logger;
   std::vector<std::unique_ptr<ClientListenerService>> listeners;
};
