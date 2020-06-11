#pragma once
#include "AsmNetLib/Ip4Addr.hpp"
#include "AsmNetLib/TCPServerSocket.hpp"
#include "cpptinytools/ILogger.hpp"

/// <summary>
/// Runs on given address and with random port
/// </summary>
class ClientListenerService
{
public:
   ClientListenerService(const ctt::log::ILogger& loggerRef, const anl::Ip4Addr& addr);
   ~ClientListenerService();


   void run();

   std::string toString() const;

private:
   const ctt::log::ILogger& logger;
   anl::TCPServerSocketUPtr serverSocket;
};
