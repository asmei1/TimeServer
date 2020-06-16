#pragma once
#include <vector>
#include <chrono>

#include "AsmNetLib/InetAddress.hpp"
#include "cpptinytools/ILogger.hpp"

class SearchServerTask
{
public:
   SearchServerTask(const ctt::log::ILogger& loggerRef, const anl::InetAddress& multicastDiscoveryAddress);

   std::vector<anl::InetAddress> getServerAddresses(const std::chrono::milliseconds& waitForMS) const;

private:
   const ctt::log::ILogger& logger;
   const anl::InetAddress discoveryAddress;
};
