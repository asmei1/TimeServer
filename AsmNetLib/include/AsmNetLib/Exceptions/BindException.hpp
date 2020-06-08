#pragma once
#include "SocketException.hpp"

namespace anl
{
   class BindException : public SocketException
   {
   public:

      explicit BindException(int bindError)
         : SocketException("Bind failed. ", bindError)
      {
      }
   };
}
