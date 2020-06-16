#include "SyncTimeService.hpp"

#include <thread>
#include <iomanip>
#include <sstream>

#include "TimeProtocol.hpp"


using TimePoint = std::chrono::system_clock::time_point;
std::string serializeTimePoint(const TimePoint& time, const std::string& format)
{
   std::time_t tt = std::chrono::system_clock::to_time_t(time);
   std::tm tm = *std::gmtime(&tt); //GMT (UTC)
   //std::tm tm = *std::localtime(&tt); //Locale time-zone, usually UTC by default.
   std::stringstream ss;
   ss << std::put_time(&tm, format.c_str());
   return ss.str();
}


SyncTimeService::SyncTimeService(const ctt::log::ILogger& loggerRef)
   : logger(loggerRef)
{

}

SyncTimeService::~SyncTimeService()
{
   this->disconnect();
}

bool SyncTimeService::connectTo(const anl::InetAddress& address)
{
   try
   {
      this->socket = std::make_unique<anl::TCPSocket>();
      this->socket->connectTo(address);
      return true;
   }
   catch(...)
   {
      return false;
   }
}

void SyncTimeService::run(const std::chrono::milliseconds& frequency)
{
   std::thread([this, frequency] {

      this->logger.debug("Sync time");
      const auto& requestTimePacket = TimeProtocol::makeGetServerTimeCmd();
      while(true)
      {
         uint64_t clientTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

         if(false == this->socket->sendData(requestTimePacket))
         {
            this->logger.error("There was an error during sending time request to server.");
            break;
         }

         const auto& timeFromServerOpt= this->socket->recvData();

         if(true == timeFromServerOpt.has_value())
         {
            if(TimeProtocol::Command::SEND_SERVER_TIME == TimeProtocol::parseBuffer(*timeFromServerOpt))
            {
               const auto& serverTime = TimeProtocol::parseTimeFromServer(timeFromServerOpt.value());

               const uint64_t clientTimeMsAfterRequest = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

               const double delta = serverTime + (clientTimeMsAfterRequest - clientTimeMs) / 2. - serverTime;

               TimePoint tp{ std::chrono::duration_cast<TimePoint::duration>(std::chrono::milliseconds(static_cast<uint64_t>(clientTimeMsAfterRequest + delta))) };
               this->logger.info("Time:  " + serializeTimePoint(tp, "%Y-%m-%dT%H:%M:%SZ"));
               this->logger.info("Delta: " + std::to_string(delta) + "ms");
            }
         }
         else
         {
            this->logger.info("Server disconnected");
            break;
         }


         std::this_thread::sleep_for(frequency);
      }


      }).detach();
}

void SyncTimeService::disconnect()
{
   if(true == this->socket->isConnected())
   {
      this->socket->closeSocket();
   }
}
