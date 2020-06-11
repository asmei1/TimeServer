#include "ClientListenerService.hpp"

#include <random>

#include "AsmNetLib/Exceptions/BindException.hpp"

ClientListenerService::ClientListenerService(const ctt::log::ILogger& loggerRef, const anl::Ip4Addr& addr)
   : logger(loggerRef)
{
   std::mt19937 engine{std::random_device{}()};
   const std::uniform_int_distribution<uint16_t> randomPortNumberDistr(49152, 65535);

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
