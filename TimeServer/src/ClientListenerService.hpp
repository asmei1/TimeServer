#pragma once
#include "AsmNetLib/Ip4Addr.hpp"
#include "AsmNetLib/TCPServerSocket.hpp"

/// <summary>
/// Runs on given address and with random port
/// </summary>
class ClientListenerService
{
public:
   ClientListenerService(const anl::Ip4Addr& addr);
   ~ClientListenerService();


   void run();

   std::string toString() const;

private:
   anl::TCPServerSocketUPtr serverSocket;
};
