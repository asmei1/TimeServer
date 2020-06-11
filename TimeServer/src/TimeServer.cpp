#include "TimeServer.hpp"


#include "AsmNetLib/Ip4Addr.hpp"

TimeServer::TimeServer(const ctt::log::ILogger& loggerRef)
   : logger(loggerRef)
{
}

void TimeServer::initialize()
{
   for(const auto& addr : anl::Ip4Addr::getAllInterfaceAddresses())
   {
      this->listeners.push_back(std::make_unique<ClientListenerService>(this->logger, addr));
   }
}

void TimeServer::printInfo() const
{
   this->logger.info("Listening on addresses:");
   for(const auto& listener : this->listeners)
   {
      this->logger.info(listener->toString());
   }
}

void TimeServer::run()
{
   
}
