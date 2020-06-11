#include "TimeServer.hpp"


#include <iostream>
#include "AsmNetLib/Ip4Addr.hpp"

void TimeServer::initialize()
{
   for(const auto& addr : anl::Ip4Addr::getAllInterfaceAddresses())
   {
      this->listeners.push_back(std::make_unique<ClientListenerService>(addr));
   }
}

void TimeServer::printListeners() const
{
   for(const auto& listener : this->listeners)
   {
      std::cout << listener->toString() << std::endl;
   }
}

void TimeServer::run()
{
   
}
