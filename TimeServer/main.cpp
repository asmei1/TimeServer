#include <iostream>
#include "AsmNetLib/AsmNetwork.hpp"
#include "Server.hpp"

int main()
{
   if(true == anl::AsmNetwork::initialize())
   {
      Server server;
      server.run();

      anl::AsmNetwork::cleanup();
      return 0;
   }

   return -1;
}
