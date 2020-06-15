#include "TimeServer.hpp"

#include <iostream>


#include "AsmNetLib/NetworkAdapter.hpp"

TimeServer::TimeServer(const ctt::log::ILogger& loggerRef)
   : logger(loggerRef)
{
}

void TimeServer::initialize()
{
   for(const auto& adapter : anl::NetworkAdapter::getAllInterfaceAddresses())
   {
      this->listeners.push_back(std::make_unique<ClientListenerService>(this->logger, adapter));
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

void TimeServer::startServices()
{
   for(const auto& listener : this->listeners)
   {
      listener->run();
   }
}

void TimeServer::run()
{
   //startServices();
   bool running = false;
   while(true)
   {
      std::cout << "Server command line:" << std::endl
         << "run               Run listening services." << std::endl
         << "print             Print all active listener service." << std::endl
         << "clients           Print all active listener service with clients." << std::endl
         //<< "close [index]     Close connection at index." << std::endl
         << "help              Print this help" << std::endl
         << "quit              Close connection and the server." << std::endl;

      std::string command;
      std::getline(std::cin, command);

      const auto& tokens = ctt::StringTools::split(command, " ");

      if(tokens[0] == "run")
      {
         if(true == running)
         {
            startServices();
            this->printInfo();
            running = true;
         }
         else
         {
            std::cout << "Server is already running." << std::endl;
         }

      }
      else if(tokens[0] == "print")
      {
         this->printInfo();
      }
      else if(tokens[0] == "clients")
      {
         this->printServicesInfo();
      }
      /*else if(tokens[0] == "close")
      {
         this->listeners.erase(this->listeners.begin() + std::stoi(tokens[1]));
         this->printInfo();
      }*/
      else if(tokens[0] == "quit")
      {
         break;
      }
      else if(tokens[0] == "help")
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

void TimeServer::printServicesInfo() const
{
   for(const auto& service : this->listeners)
   {
      service->logInfo();
   }
}
