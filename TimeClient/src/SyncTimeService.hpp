#pragma once
#include <chrono>
#include "AsmNetLib/InetAddress.hpp"
#include "AsmNetLib/TCPSocket.hpp"
#include "cpptinytools/ILogger.hpp"


class SyncTimeService
{
public:
   SyncTimeService(const ctt::log::ILogger& loggerRef);
   ~SyncTimeService();

   bool connectTo(const anl::InetAddress& address);
   void run(const std::chrono::milliseconds& frequency);
   void disconnect();

private:
   anl::TCPSocketUPtr socket;
   const ctt::log::ILogger& logger;
};
