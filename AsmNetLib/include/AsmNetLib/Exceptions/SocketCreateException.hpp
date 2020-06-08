#pragma once
#include <stdexcept>

#include "SocketException.hpp"

namespace anl
{
   class SocketCreateException : public SocketException
   {
   public:
      explicit SocketCreateException(int bindError)
         : SocketException("Socket creation failed. ", bindError)
      {
      }

   };
}
