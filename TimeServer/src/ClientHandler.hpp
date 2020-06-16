#pragma once
#include <iostream>

#include "AsmNetLib/TCPSocket.hpp"
#include "cpptinytools/ILogger.hpp"
#include "cpptinytools/StoppableTask.hpp"

class ClientHandler
{
public:
   ClientHandler(const ctt::log::ILogger& logger, anl::TCPSocketUPtr socket);
   ~ClientHandler();

   ClientHandler(const ClientHandler& other) = delete;
   ClientHandler& operator=(const ClientHandler& other) = delete;

   void setDisconnectHandler(std::function<void(ClientHandler*)> fun);

   std::string toString() const;

private:
   class ClientHandlerTask : public ctt::StoppableTask
   {
   public:
      ClientHandlerTask(ClientHandler& clientRef)
         : client(clientRef)
      {
      }         

      void run() override;
   private:
      ClientHandler& client;
   };

   ClientHandlerTask* task;

   std::function<void(ClientHandler*)> disconnectSignal;
   
   const ctt::log::ILogger& logger;
   anl::TCPSocketSPtr socket;
};
