#include "TimeServer.hpp"


#include <iostream>

#include "AsmNetLib/Ip4Addr.hpp"

void TimeServer::run()
{
   for(const auto& addr : anl::Ip4Addr::getAllInterfaceAddresses())
   {
      std::cout << addr.toString() << std::endl;
   }
}
