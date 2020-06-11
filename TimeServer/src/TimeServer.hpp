#pragma once
#include <vector>

#include "ClientListenerService.hpp"

class TimeServer
{
public:
   void initialize();
   void printListeners() const;
   void run();

private:
   std::vector<std::unique_ptr<ClientListenerService>> listeners;
};
