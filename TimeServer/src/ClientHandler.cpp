#include "ClientHandler.hpp"

ClientHandler::ClientHandler(const ctt::log::ILogger& loggerRef, anl::TCPSocketUPtr clientSocket)
   : logger(loggerRef), socket(std::move(clientSocket))
{
   this->task = new ClientHandlerTask(*this);
   std::thread handlerThread(&ClientHandlerTask::run, this->task);
   handlerThread.detach();
}

ClientHandler::~ClientHandler()
{
   this->socket->closeSocket();
   this->task->stop();
   delete this->task;
}

void ClientHandler::setDisconnectHandler(std::function<void(ClientHandler*)> fun)
{
   this->disconnectSignal = fun;
}

std::string ClientHandler::toString() const
{
   return this->socket->getSocketAddress().toString();
}

void ClientHandler::ClientHandlerTask::run()
{
   while(true)
   {
      const auto& data = this->client.socket->recvData();

      if(false == data.has_value())
      {
         break;
      }

      if(true == this->stopRequested())
      {
         break;
      }

      this->client.logger.info({ data.value().begin(), data.value().end() });
   }

   this->client.disconnectSignal(&this->client);
}
