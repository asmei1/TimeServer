#include "DiscoverListener.hpp"


#include "TimeProtocol.hpp"
#include "AsmNetLib/Exceptions/SocketException.hpp"
#include "AsmNetLib/UDPSocket.hpp"

DiscoverListener::DiscoverListener(const ctt::log::ILogger& loggerRef, uint16_t portNumber, const anl::InetAddress& socketAddr, const anl::InetAddress& mutlicastGroupAddress)
   : logger(loggerRef), servicePortNumber(portNumber), socket(socketAddr), mutlicastAddress(mutlicastGroupAddress), socketAddress(socketAddr)
{
   this->socket.joinToGroup(mutlicastGroupAddress.getAddress());
   this->task = new DiscoverTask(this);
}

DiscoverListener::~DiscoverListener()
{
   this->socket.closeSocket();
   delete this->task;
}

void DiscoverListener::startListening()
{
   std::thread discoverTaskThread(&DiscoverTask::run, this->task);
   discoverTaskThread.detach();
}

void DiscoverListener::DiscoverTask::run()
{
   const std::string command = "OFFER ADDRESS " + this->listener->socketAddress.toString();
   const anl::Data toSend = { command.begin(), command.end() };
   while(true)
   {
      anl::Data data;
      try
      {
         auto recvAddress = this->listener->socket.recvData(data);
         if(TimeProtocol::Command::DISCOVERY == TimeProtocol::parseBuffer(data))
         {
            anl::UDPSocket().sendData(toSend, recvAddress);
         }
         else
         {
            this->listener->logger.warning("Discover service get not recognized command: " + std::string{ data.begin(), data.end() });
         }

         if(true == this->stopRequested())
         {
            break;
         }
      }
      catch(anl::SocketException& e)
      {
         //Socket, when closed can throw a -1 or WSAEINTR exception due to force close blocking operation (recfrom)
         if(e.getErrorCode() != -1 && e.getErrorCode() != WSAEINTR)
         {
            this->listener->logger.error(std::string("There was an error in discovery task.") + e.what());
         }
         break;
      }
   }
}
