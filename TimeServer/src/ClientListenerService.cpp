#include "ClientListenerService.hpp"

#include <random>

#include "AsmNetLib/Exceptions/BindException.hpp"
#include "AsmNetLib/TCPSocket.hpp"

ClientListenerService::ClientListenerService(const ctt::log::ILogger& loggerRef, const anl::NetworkAdapter& adapter)
   : logger(loggerRef), networkAdapter(adapter)
{
   std::mt19937 engine{ std::random_device{}() };
   const std::uniform_int_distribution<uint16_t> randomPortNumberDistr(49152, 65535);

   //rand number until get free port
   while(true)
   {
      try
      {
         this->serverSocket = std::make_unique<anl::TCPServerSocket>(anl::InetAddress{ this->networkAdapter.getAddress(), randomPortNumberDistr(engine) });
         //this->serverSocket = std::make_unique<anl::TCPServerSocket>(anl::InetAddress{ addr, 666});
         break;
      }
      catch(anl::BindException& e)
      {
      }
   }

   //initialize handler function for new clients
   this->serverSocket->registerClientConnectedHandler(std::bind(&ClientListenerService::handleNewClient, this, std::placeholders::_1));
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
   return this->networkAdapter.getAdapterName() + ": " + this->serverSocket->getAddress().toString();
}

void ClientListenerService::handleNewClient(anl::TCPSocketUPtr newClientSocket)
{
   std::lock_guard(this->clientCrudMutex);
   this->logger.info("New client connected: " + newClientSocket->getSocketAddress().toString());
   auto client = std::make_unique<ClientHandler>(this->logger, std::forward<anl::TCPSocketUPtr>(newClientSocket));
   client->setDisconnectHandler(std::bind(&ClientListenerService::clientDisconnected, this, std::placeholders::_1));
   this->clients.push_back(std::move(client));
}

void ClientListenerService::clientDisconnected(ClientHandler* handler)
{
   std::lock_guard(this->clientCrudMutex);

   this->logger.info("Client disconnected");
   this->clients.erase(std::find_if(this->clients.cbegin(), this->clients.cend(),
      [handler](const auto& ptr) { return handler == ptr.get(); }));
}

void ClientListenerService::logInfo() const
{
   int index = 0;
   std::string log;

   log += this->toString();
   log += "\n";

   for(const auto& client : this->clients)
   {
      log += "\t";
      log += "[" + std::to_string(index++) + "] ";
      log += client->toString();
      log += "\n";
   }

   if(true == this->clients.empty())
   {
      log += "No clients.\n";
   }

   this->logger.info(log);
}
