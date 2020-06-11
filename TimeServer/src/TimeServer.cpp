#include "TimeServer.hpp"

#include <iostream>


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
   std::cout << "Listening on addresses:" << std::endl;
   int index = 0;
   for(const auto& listener : this->listeners)
   {
      std::cout << "[" << index++ << "] " << listener->toString() << std::endl;
   }
}

void TimeServer::run()
{
   for(const auto& listener : this->listeners)
   {
      listener->run();
   }

   while(true)
   {
      std::cout << "Server command line:" << std::endl
         << "print             Print all active listener service." << std::endl
         << "close [index]     Close connection at index." << std::endl
         << "quit              Close connection and the server." << std::endl;

      std::string command;
      std::getline(std::cin, command);

      const auto& tokens = ctt::StringTools::split(command, " ");

      if(tokens[0] == "print")
      {
         this->printInfo();
      }
      else if(tokens[0] == "close")
      {
         this->listeners.erase(this->listeners.begin() + std::stoi(tokens[1]));
         this->printInfo();
      }
      else if(tokens[0] == "quit")
      {
         break;
      }
      
   }
}
