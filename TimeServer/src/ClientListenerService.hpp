#pragma once
#include "ClientHandler.hpp"
#include "AsmNetLib/Ip4Addr.hpp"
#include "AsmNetLib/NetworkAdapter.hpp"
#include "AsmNetLib/TCPServerSocket.hpp"
#include "cpptinytools/ILogger.hpp"

/// <summary>
/// Runs on given address and with random port
/// </summary>
class ClientListenerService
{
public:
   ClientListenerService(const ctt::log::ILogger& loggerRef, const anl::NetworkAdapter& adapter);
   ~ClientListenerService();


   void run();

   std::string toString() const;

   void handleNewClient(anl::TCPSocketUPtr newClientSocket);
   void clientDisconnected(ClientHandler* handler);
   void logInfo() const;

private:
   std::vector<std::unique_ptr<ClientHandler>> clients;
   std::mutex clientCrudMutex;

   const ctt::log::ILogger& logger;
   anl::TCPServerSocketUPtr serverSocket;
   anl::NetworkAdapter networkAdapter;
};
