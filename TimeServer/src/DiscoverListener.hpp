#pragma once
#include "AsmNetLib/InetAddress.hpp"
#include "AsmNetLib/MulticastSocket.hpp"
#include "cpptinytools/ILogger.hpp"
#include "cpptinytools/StoppableTask.hpp"

class DiscoverListener
{
public:
   DiscoverListener(const ctt::log::ILogger& logger, uint16_t portNumber, const anl::InetAddress& socketAddr, const anl::InetAddress& mutlicastGroupAddress);
   ~DiscoverListener();

   void startListening();

private:
   class DiscoverTask : public ctt::StoppableTask
   {
   public:
      DiscoverTask(DiscoverListener* listenerPtr)
         : listener(listenerPtr)
      {}

      void run() override;
   private:
      DiscoverListener* listener;
   };

   const ctt::log::ILogger& logger;

   const uint16_t servicePortNumber;
   DiscoverTask* task;

   anl::MulticastSocket socket;
   anl::InetAddress mutlicastAddress;
   anl::InetAddress socketAddress;
};
