#include "ClientListenerService.hpp"

#include <iostream>

#include <random>

#include "AsmNetLib/Exceptions/BindException.hpp"

ClientListenerService::ClientListenerService(const anl::Ip4Addr& addr)
{
   std::mt19937 engine{std::random_device{}()};
   std::uniform_int_distribution<uint16_t> randomPortNumberDistr(49152, 65535);

   //rand number until get free port
   while(true)
   {
      try
      {
         this->serverSocket = std::make_unique<anl::TCPServerSocket>(anl::InetAddress{ addr, randomPortNumberDistr(engine) });
         break;
      }
      catch (anl::BindException& e)
      {
         //std::cerr << e.what() << std::endl;
      }
   }

}

ClientListenerService::~ClientListenerService()
{

}

void ClientListenerService::run()
{

}

std::string ClientListenerService::toString() const
{
   return this->serverSocket->getAddress().toString();
}
