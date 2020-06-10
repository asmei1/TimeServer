#include <iostream>
#include "AsmNetLib/AsmNetwork.hpp"
#include "TimeServer.hpp"

int main()
{
   if(true == anl::AsmNetwork::initialize())
   {
      TimeServer server;
      server.run();

      anl::AsmNetwork::cleanup();
      return 0;
   }

   return -1;
}
