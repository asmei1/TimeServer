#include "SearchServerTask.hpp"

#include <thread>
#include <execution>

#include "TimeProtocol.hpp"
#include "AsmNetLib/MulticastSocket.hpp"
#include "AsmNetLib/NetworkAdapter.hpp"
#include "AsmNetLib/Exceptions/SocketException.hpp"

SearchServerTask::SearchServerTask(const ctt::log::ILogger& loggerRef, const anl::InetAddress& multicastDiscoveryAddress)
   : logger(loggerRef), discoveryAddress(multicastDiscoveryAddress)
{
}

std::vector<anl::InetAddress> SearchServerTask::getServerAddresses(const std::chrono::milliseconds& waitForMS) const
{
   std::mutex mutex;
   std::vector<anl::InetAddress> addresses;

   try
   {
      std::vector<anl::MulticastSocketSPtr> sockets;

      for(const auto& adapter : anl::NetworkAdapter::getAllInterfaceAddresses())
      {
         auto socket = std::make_shared<anl::MulticastSocket>(anl::InetAddress(adapter.getAddress(), 0));
         sockets.push_back(std::move(socket));
      }

      for(auto socket : sockets)
      //std::for_each(std::execution::par, sockets.begin(), sockets.end(), [&](const anl::MulticastSocketSPtr& socket)
         {
            std::thread([socket, &addresses, &mutex, this]
               {
                  try
                  {
                     socket->sendData(TimeProtocol::makeDiscoveryCmd(), this->discoveryAddress);
                  }
                  catch(...)
                  {
                     return;
                  }

                  anl::Data recvData;
                  while(true)
                  {
                     recvData.clear();
                     try
                     {
                        socket->recvData(recvData);
                        if(TimeProtocol::Command::SEND_OFFER == TimeProtocol::parseBuffer(recvData))
                        {
                           const auto& optAddr = TimeProtocol::parseOfferAddress(recvData);
                           if(true == optAddr.has_value())
                           {
                              std::lock_guard<std::mutex>{mutex};
                              addresses.push_back(optAddr.value());
                           }
                        }
                     }
                     catch(...)
                     {
                        break;
                     }

                  }

               }).detach();
         //});
      }

      std::this_thread::sleep_for(waitForMS);
      for(auto& socket : sockets)
      {
         socket->closeSocket();
      }
      sockets.clear();
   }
   catch(const anl::SocketException& e)
   {
      this->logger.error(std::string("Error during discovering servers. ") + e.what());
   }

   return addresses;
}
