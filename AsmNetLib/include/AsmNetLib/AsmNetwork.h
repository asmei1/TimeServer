#pragma once
#include "NetworkHeaders.hpp"

namespace anl
{
   class AsmNetwork
   {
   public:
      static bool initialize();
      static int cleanup();
   private:
      static inline WSADATA wsa;
   };
}

