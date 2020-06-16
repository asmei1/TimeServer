#include "SearchServerTask.hpp"

#include <ostream>
#include <thread>



#include "TimeProtocol.hpp"
#include "AsmNetLib/MulticastSocket.hpp"
#include "AsmNetLib/Exceptions/SocketException.hpp"

SearchServerTask::SearchServerTask(const ctt::log::ILogger& loggerRef, const anl::InetAddress& multicastDiscoveryAddress)
   : logger(loggerRef), discoveryAddress(multicastDiscoveryAddress)
{
}

std::vector<anl::InetAddress> SearchServerTask::getServerAddresses(const std::chrono::milliseconds& waitForMS) const
{
   std::vector<anl::InetAddress> addresses;

   try
   {
      anl::MulticastSocket socket;
      std::thread listeningThread([&socket, &addresses, this]
         {
            socket.sendData(TimeProtocol::makeDiscoveryCmd(), this->discoveryAddress);

            anl::Data recvData;
            while(true)
            {
               recvData.clear();
               try
               {
                  auto a = socket.recvData(recvData);
                  if(TimeProtocol::Command::SEND_OFFER == TimeProtocol::parseBuffer(recvData))
                  {
                     const auto& optAddr = TimeProtocol::parseOfferAddress(recvData);
                     if(true == optAddr.has_value())
                     {
                        addresses.push_back(optAddr.value());
                     }
                  }
               }
               catch(...)
               {
                  break;
               }

            }

         });
      listeningThread.detach();
      //listeningThread.join();

      std::this_thread::sleep_for(waitForMS);

      socket.closeSocket();
   }
   catch(const anl::SocketException& e)
   {
      this->logger.error(std::string("Error during discovering servers. ") + e.what());
   }

   return addresses;
}
