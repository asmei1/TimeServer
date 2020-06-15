#pragma once
#include "NetworkHeaders.hpp"
#include "Ip4Addr.hpp"

namespace anl
{
   class NetworkAdapter
   {
   public:
      NetworkAdapter(const Ip4Addr& addr, const std::string& name)
         : address(addr), adapterName(name)
      {}

      Ip4Addr getAddress() const
      {
         return this->address;
      }

      std::string getAdapterName() const
      {
         return this->adapterName;
      }

      static std::vector<anl::NetworkAdapter> getAllInterfaceAddresses()
      {
         addrinfo hints;

         memset(&hints, 0, sizeof(hints));
         hints.ai_family = AF_INET;
         hints.ai_flags = AI_CANONNAME;
         addrinfo* result = nullptr;
         //--------------------------------
         // Call getaddrinfo(). If the call succeeds,
         // the result variable will hold a linked list
         // of addrinfo structures containing response
         // information
         std::vector<anl::NetworkAdapter> rV;
         if(0 == getaddrinfo("..localmachine", nullptr, &hints, &result))
         {
            // Retrieve each address 
            for(auto ptr = result; ptr != NULL; ptr = ptr->ai_next)
            {
               switch(ptr->ai_family) {
                  case AF_INET:
                     rV.push_back({ anl::Ip4Addr::fromULong(htonl(reinterpret_cast<sockaddr_in*>(ptr->ai_addr)->sin_addr.S_un.S_addr)), result->ai_canonname });
                     break;
                  default:
                     break;
               }
            }

            freeaddrinfo(result);
         }
         return rV;
      }

   private:
      Ip4Addr address;
      std::string adapterName;
   };
   
}
