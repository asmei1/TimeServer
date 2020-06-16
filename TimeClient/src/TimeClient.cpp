#include "TimeClient.hpp"


#include <iostream>
#include <thread>

#include "SearchServerTask.hpp"

TimeClient::TimeClient(const ctt::log::ILogger& loggerRef)
   : logger(loggerRef)
{
}

void TimeClient::run()
{
   SearchServerTask task{ this->logger, anl::InetAddress(anl::Ip4Addr::fromString("224.0.0.10").value(), 7) };
   while(true)
   {
      int index = 0;
      for(const auto& addr : task.getServerAddresses(std::chrono::milliseconds(1000)))
      {
         std::cout << "[" << index++ << "] " << addr.toString() << std::endl;
      }
      std::cout << std::endl;

      std::this_thread::sleep_for(std::chrono::seconds(10));
   }
}
