#pragma once

#include <stdexcept>
#include <string>

namespace anl
{
   class SocketException : public std::runtime_error
   {
   public:
      explicit SocketException(int errorCode)
         : runtime_error("Socket exception: " + std::to_string(errorCode))
      {
         this->errorCode = errorCode;
      }

      explicit SocketException(const std::string& msg, int errorCode)
         : runtime_error(msg + std::to_string(errorCode))
      {
         this->errorCode = errorCode;
      }



      int getErrorCode() const
      {
         return this->errorCode;
      }

   private:
      int errorCode;
   };
}
