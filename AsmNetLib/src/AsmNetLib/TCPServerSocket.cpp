#include "TCPServerSocket.hpp"
#include <cassert>

#include "TCPSocket.hpp"
using namespace anl;

TCPServerSocket::TCPServerSocket(const InetAddress& address)
{
   this->socketDesc.bind(address);
}

TCPServerSocket::~TCPServerSocket()
{
   stopListening();
}

void TCPServerSocket::startListening()
{
   //create task to listening
   this->worker = new ClientsListeningTask(this);
   this->listeningThread = std::thread(&ctt::StoppableTask::run, this->worker);
}


void TCPServerSocket::stopListening()
{
   if(this->listening)
   {
      //clear flags
      this->listening = false;

      //close socket and listening task
      this->socketDesc.closeSocket();
      this->worker->stop();
      this->listeningThread.join();
      delete this->worker;
      this->worker = nullptr;
   }
}

void TCPServerSocket::pauseListening()
{
   if(nullptr != this->worker)
   {
      this->worker->pause();
   }
}

void TCPServerSocket::resumeListening()
{
   if(nullptr != this->worker)
   {
      this->worker->resume();
   }
}

void TCPServerSocket::registerClientConnectedHandler(const ClientConnectedHandler& handler)
{
   this->clientConnectionHandler = handler;
}

InetAddress TCPServerSocket::getAddress() const
{
   return this->socketDesc.toInetAddress();
}

void TCPServerSocket::ClientsListeningTask::run()
{
   while(true)
   {
      this->waitIfPaused();

      auto socket = this->socket->socketDesc.accept();
   
      //if stopListening method was executed, break the loop
      if(true == this->stopRequested())
      {
         break;
      }

      //if something went wrong
      if(false == socket.has_value())
      {
         break;
      }

      //if everything is okey, execute callback function
      this->socket->clientConnectionHandler(TCPSocketUPtr(new TCPSocket(socket.value())));
   }
}
