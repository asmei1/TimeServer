#include <iostream>

#include "AsmNetLib/AsmNetwork.hpp"
#include "AsmNetLib/TCPSocket.hpp"
#include "AsmNetLib/UDPSocket.hpp"
#include "AsmNetLib/SocketDescription.hpp"
#include "AsmNetLib/MulticastSocket.hpp"
#include "AsmNetLib/InetAddress.hpp"
#include "AsmNetLib/Exceptions/SocketException.hpp"
#include "AsmNetLib/Exceptions/TimeoutException.hpp"

int main()
{
   anl::AsmNetwork::initialize();

   anl::InetAddress bindAddr{ anl::Ip4Addr::fromString("192.168.88.247").value(), 7 };
   anl::InetAddress discoveryAddress(anl::Ip4Addr::fromString("224.0.0.10").value(), 7);


   const std::string command = "DISCOVERY";
   const anl::Data toSend = { command.begin(), command.end() };

   //anl::InetAddress bindAddr{ anl::Ip4Addr::any(), 7 };

   //anl::MulticastSocket().sendData(toSend, discoveryAddress);

   anl::MulticastSocket socket;
   socket.sendData(toSend, discoveryAddress);
   //socket.sendData(toSend, discoveryAddress);
   anl::Data recvData;
   auto a = socket.recvData(recvData);
   std::cout << std::string{recvData.begin(), recvData.end()} << std::endl;




   //auto test = getAllInterfaceAddresses();
   //for(const auto& addr : anl::getAllInterfaceAddresses())
   //{
   //   std::cout << addr.toString() << std::endl;
   //}
   //printf("Calling getaddrinfo with following parameters:\n");
   //try
   //{
      //auto addr = anl::InetAddress{ "192.168.88.247", 666 };
      //auto socketBeforeCopy = ::socket(AF_INET, SOCK_STREAM, 0);
      //sockaddr_in rVBeforeCopy;
      //memset(static_cast<void*>(&rVBeforeCopy), 0, sizeof(sockaddr_in));
      //rVBeforeCopy.sin_family = AF_INET;
      //rVBeforeCopy.sin_addr.S_un.S_addr = addr.getAddress();
      //rVBeforeCopy.sin_port = htons(addr.getPort());
      //auto rV = rVBeforeCopy;
      //auto socket = socketBeforeCopy;
      //int size = sizeof(sockaddr_in);
      //bool success = 0 <= connect(socket, reinterpret_cast<sockaddr*>(&rV), size);


   //   const auto& addr = anl::InetAddress{ "192.168.88.247", 666 };
   //   const auto& localhost = anl::InetAddress{ "127.0.0.1", 6666 };
   //   const std::string rawData = "THIS DATA WAS SENT1123";
   //   const anl::Data data = { rawData.cbegin(), rawData.cend() };

   //   ////tcp
   //   //{
   //   //   anl::TCPSocket testSocket;
   //   //   testSocket.connectTo(addr);
   //   //   testSocket.sendData(data);

   //   //   const auto& rec = testSocket.recvData();

   //   //   std::cout << (rec ? std::string{ rec.value().cbegin(), rec.value().cend() } : "error") << std::endl;

   //   //   testSocket.closeSocket();
   //   //}

   //   //udp
   //   {
   //      //anl::Data recData;
   //      //anl::UDPSocket udpSocket;
   //      ///*udpSocket.sendData(data, addr);
   //      //const auto& recAddr = udpSocket.recvData(recData);

   //      //std::cout << recAddr.toString() << std::endl;
   //      //std::cout << std::string{ recData.cbegin(), recData.cend() } << std::endl;*/

   //      ////recData.clear();
   //      ////udpSocket.sendData(data, addr);
   //      ////udpSocket.recvDataFrom(recData, localhost);
   //      ////std::cout << std::string{ recData.cbegin(), recData.cend() } << std::endl;

   //      ////anl::UDPSocket as;
   //      ////try
   //      ////{
   //      ////   std::cout << "should thrown timeout? ...." << std::endl;
   //      ////   udpSocket.sendData(data, addr);
   //      ////   as.recvDataFrom(recData, addr);
   //      ////   std::cout << std::string{ recData.cbegin(), recData.cend() } << std::endl;
   //      ////}
   //      ////catch(anl::TimeoutException& e)
   //      ////{
   //      ////   std::cout << "and throw" << std::endl;
   //      ////}


   //      //udpSocket.closeSocket();
   //   }

   //   //{
   //   //   int in = 0;
   //   //   std::cin >> in;

   //   //   if(in == 0)
   //   //   {
   //   //      anl::MulticastSocket().sendData(data, anl::InetAddress{ "224.0.0.10", 666 });
   //   //   }
   //   //   else
   //   //   {
   //   //      anl::Data recData;
   //   //      anl::MulticastSocket multicast;
   //   //      multicast.bind(addr);
   //   //      multicast.joinToGroup(anl::InetAddress{ "224.0.0.10", 0 });
   //   //      multicast.recvData(recData);
   //   //      std::cout << std::string{ recData.cbegin(), recData.cend() } << std::endl;
   //   //   }
   //   //}

   //}
   //catch(anl::SocketException e)
   //{
   //   std::cout << "Something went not too good, error code " << e.getErrorCode();
   //}


   anl::AsmNetwork::cleanup();
   return 0;
}
