#pragma once
#include <thread>
#include <atomic>

#include "cpptinytools/ResumableTask.hpp"
#include "NetworkHeaders.hpp"
#include "SocketDescription.hpp"

namespace anl
{

   class TCPServerSocket
   {
   public:
      TCPServerSocket(const InetAddress& address);

      ~TCPServerSocket();

      void startListening();
      void stopListening();

      void pauseListening();
      void resumeListening();

      void registerClientConnectedHandler(const ClientConnectedHandler& handler);

   private:
      class ClientsListeningTask : public ctt::ResumableTask
      {
      public:
         ClientsListeningTask(TCPServerSocket* serverSocket) : socket(serverSocket) {}
         void run() override;
      private:
         TCPServerSocket* socket;
      };
      ClientsListeningTask* worker;
      std::thread listeningThread;

      std::atomic_bool listening = false;
      ClientConnectedHandler clientConnectionHandler;

      int portNumber;
      SocketDescription socketDesc{ SocketDescription::SocketType::TCP, IPPROTO_TCP };
   };
}

