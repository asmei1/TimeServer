#pragma once
#include "SyncTimeService.hpp"
#include "AsmNetLib/InetAddress.hpp"
#include "cpptinytools/ILogger.hpp"
#include "cpptinytools/ResumableTask.hpp"

class TimeClient
{
public:
   TimeClient(const ctt::log::ILogger& loggerRef);
   ~TimeClient();

   void run();

private:
   int getFrequencyFromUser() const;

   void runSyncTimeService(const anl::InetAddress& address);
   void handleConnectCommand(const std::string& cmdToken);
   std::optional<anl::InetAddress> getDiscoveredAddressAt(int index) const;


   class DiscoveryService : public ctt::ResumableTask
   {
   public:
      DiscoveryService(TimeClient& timeClient)
         : client(timeClient){}

      void run() override;
      void stop();
   private:
      TimeClient& client;
   } discoverService;
   std::thread discoverThread;


   SyncTimeService syncTimeService;

   std::atomic_bool connected = false;
   mutable std::mutex mutexForAddresses;
   std::vector<anl::InetAddress> discoveredAddresses;

   //last ip address, where client was connected to
   std::optional<anl::InetAddress> lastServerAddress = std::nullopt;

   const ctt::log::ILogger& logger;
};
