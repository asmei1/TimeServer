#pragma once
#include "NetworkHeaders.hpp"

namespace anl
{
   class AsmNetwork
   {
   public:
      static bool initialize(ILogger* loggerInstance);
      static int cleanup();
      static ILogger* getLogger();
   private:
      static inline WSADATA wsa;
      static inline ILogger* logger;
   };
}

