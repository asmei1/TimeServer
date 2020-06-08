#include <iostream>
#include "AsmNetLib/AsmNetwork.hpp"
#include "AsmNetLib/TCPSocket.hpp"
#include "AsmNetLib/Exceptions/SocketException.hpp"

int main()
{
   anl::AsmNetwork::initialize();
   try
   {
      const std::string data = "THIS DATA WAS SENT";
      anl::TCPSocket testSocket;
      testSocket.connectTo({ "192.168.88.247", 666 });
      testSocket.sendData({ data.cbegin(), data.cend() });

      const auto& rec = testSocket.recvData();

      std::cout << (rec ? std::string{ rec.value().cbegin(), rec.value().cend() } : "error") << std::endl;

      testSocket.closeSocket();
   }
   catch( anl::SocketException e )
   {
      std::cout << "Something went not too good";
   }


   anl::AsmNetwork::cleanup();
   return 0;
}
