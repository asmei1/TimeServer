#include "ClientListenerService.hpp"

#include <random>

#include "AsmNetLib/Exceptions/BindException.hpp"
#include "AsmNetLib/TCPSocket.hpp"

ClientListenerService::ClientListenerService(const ctt::log::ILogger& loggerRef, const anl::Ip4Addr& addr)
   : logger(loggerRef)
{
   std::mt19937 engine{ std::random_device{}() };
   const std::uniform_int_distribution<uint16_t> randomPortNumberDistr(49152, 65535);

   //rand number until get free port
   while(true)
   {
      try
      {
         this->serverSocket = std::make_unique<anl::TCPServerSocket>(anl::InetAddress{ addr, randomPortNumberDistr(engine) });
         //this->serverSocket = std::make_unique<anl::TCPServerSocket>(anl::InetAddress{ addr, 666});
         break;
      }
      catch(anl::BindException& e)
      {
      }
   }

   //initialize handler function for new clients
   this->serverSocket->registerClientConnectedHandler([this](anl::TCPSocketUPtr newClientSocket)
      {
         this->logger.info(newClientSocket->getSocketAddress().toString());
      });
}

ClientListenerService::~ClientListenerService()
{
}

void ClientListenerService::run()
{
   this->serverSocket->startListening();
}

std::string ClientListenerService::toString() const
{
   return this->serverSocket->getAddress().toString();
}
