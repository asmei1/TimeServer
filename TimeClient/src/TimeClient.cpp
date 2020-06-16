#include "TimeClient.hpp"


#include <iostream>
#include <thread>

#include "SearchServerTask.hpp"
#include "SyncTimeService.hpp"

TimeClient::TimeClient(const ctt::log::ILogger& loggerRef)
   : logger(loggerRef), discoverService(*this), syncTimeService(loggerRef)
{
   this->discoverThread = std::thread(std::ref(this->discoverService));
}

TimeClient::~TimeClient()
{
   this->discoverService.stop();

   if(true == this->discoverThread.joinable())
   {
      this->discoverThread.join();
   }
}

void TimeClient::run()
{
   while(true)
   {
      std::cout << "Time client command line: " << std::endl
         << "connect [index]           Connect to discovered server on given index" << std::endl
         << "connect [ip:port]         Try to connect to server on given ip and port" << std::endl
         << "disconnect                Disconnect from server" << std::endl
         << "help                      Print this help" << std::endl
         << "quit                      Close connection and application" << std::endl;

      std::string cmd;
      std::getline(std::cin, cmd);

      const auto& cmdTokens = ctt::StringTools::split(cmd, " ");
      if(false == cmdTokens.empty())
      {
         if("connect" == cmdTokens[0] && cmdTokens.size() == 2)
         {
            handleConnectCommand(cmdTokens[1]);
         }
         else if("disconnect" == cmdTokens[0])
         {
            if(true == this->connected)
            {
               this->connected = false;
               this->discoverService.resume();
               this->syncTimeService.disconnect();
            }
            else
            {
               std::cout << "No connection" << std::endl;
            }
         }
         else if("quit" == cmdTokens[0])
         {
            break;
         }
         else if("help" == cmdTokens[0])
         {
            continue;
         }
         else
         {
            std::cout << "Wrong command" << std::endl;
         }

         std::cout << std::endl;
      }
   }
}

int TimeClient::getFrequencyFromUser() const
{
   std::string msStr;
   int ms = 0;
   do
   {
      std::cout << "Input frequency (in ms) [10-1000]" << std::endl;

      std::getline(std::cin, msStr);
      try
      {
         ms = std::stoi(msStr);
      }
      catch(...) {}
   } while(ms < 10 || ms > 1000);


   return ms;
}

void TimeClient::runSyncTimeService(const anl::InetAddress& address)
{
   if(false == this->connected)
   {
      //turn off discovering (and drawing!) servers
      this->connected = true;

      if(true == this->syncTimeService.connectTo(address))
      {
         this->lastServerAddress = address;
         this->discoverService.pause();

         const int ms = getFrequencyFromUser();
         this->syncTimeService.run(std::chrono::milliseconds(ms));
      }
      else
      {
         this->connected = false;
         this->logger.error("Error during initialize sync time service");
      }
   }
}

void TimeClient::handleConnectCommand(const std::string& cmdToken)
{
   const auto& connectTokens = ctt::StringTools::split(cmdToken, ":");
   std::optional<anl::InetAddress> optAddress = std::nullopt;
   try
   {
      if(connectTokens.size() == 2)
      {
         //connect to given socket by user
         const auto& optIp = anl::Ip4Addr::fromString(connectTokens[0].c_str());
         const uint16_t port = std::stoi(connectTokens[1]);
         if(true == optIp.has_value())
         {
            optAddress = anl::InetAddress{ optIp.value(), port };
         }
      }
      else
      {
         //connect to discovered server
         optAddress = this->getDiscoveredAddressAt(std::stoi(connectTokens[0]));
      }
   }
   catch(const std::invalid_argument&)
   {
      this->logger.error("Wrong parameter passed to \"connect\" command");
   }



   if(true == optAddress.has_value())
   {
      runSyncTimeService(optAddress.value());
   }
   else
   {
      this->logger.error("Wrong parameter passed to \"connect\" command");
   }
}

std::optional<anl::InetAddress> TimeClient::getDiscoveredAddressAt(int index) const
{
   std::optional<anl::InetAddress> rV = std::nullopt;

   std::lock_guard(this->mutexForAddresses);
   if(index < this->discoveredAddresses.size())
   {
      rV = this->discoveredAddresses[index];
   }

   return rV;
}

void TimeClient::DiscoveryService::run()
{
   SearchServerTask task{ this->client.logger, anl::InetAddress(anl::Ip4Addr::fromString("224.0.0.10").value(), 7) };

   while(true)
   {
      this->waitIfPaused();

      if(true == this->stopRequested())
      {
         break;
      }

      const auto& addresses = task.getServerAddresses(std::chrono::milliseconds(1000));

      {
         std::lock_guard(this->client.mutexForAddresses);
         //if there any different servers
         if(this->client.discoveredAddresses != addresses)
         {
            this->client.discoveredAddresses = addresses;

            if(false == this->client.connected)
            {
               int index = 0;
               for(const auto& addr : task.getServerAddresses(std::chrono::milliseconds(1000)))
               {
                  //mark last connected to address
                  if(true == this->client.lastServerAddress.has_value() && addr == this->client.lastServerAddress.value())
                  {
                     std::cout << "*";
                  }

                  std::cout << "[" << index++ << "] " << addr.toString() << std::endl;
               }
               std::cout << std::endl;
            }
         }
      }

      std::this_thread::sleep_for(std::chrono::seconds(10));
   }
}

void TimeClient::DiscoveryService::stop()
{
   this->stop();
}
