cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

set(libinclude 
   "include/AsmNetLib/AsmNetLib.hpp"
   #"include/AsmNetLib/Types.h"
   #"include/AsmNetLib/ILogger.hpp"
   #"include/AsmNetLib/AsmNetwork.h"
   #"include/AsmNetLib/MulticastSocket.h"
   #"include/AsmNetLib/UDPSocket.h"
   #"include/AsmNetLib/TCPSocket.h"
   #"include/AsmNetLib/TCPServerSocket.h"
   #"include/AsmNetLib/ResumableTask.hpp"
   #"include/AsmNetLib/InetAddress.h"
   #"include/AsmNetLib/Exceptions/BindException.h"
   #"include/AsmNetLib/Exceptions/TCPServerSocketCreateException.h"
   #"include/AsmNetLib/Exceptions/TimeoutException.h"
   #"include/AsmNetLib/Exceptions/DatagramSizeOutOfRangeException.h"
   )

set(libsrc 
   "src/AsmNetLib/AsmNetwork.cpp"
   "src/AsmNetLib/BasicLogger.cpp"
   "src/AsmNetLib/MulticastSocket.cpp"
   "src/AsmNetLib/TCPServerSocket.cpp"
   "src/AsmNetLib/TCPSocket.cpp"
   "src/AsmNetLib/UDPSocket.cpp"
   "src/AsmNetLib/Helper.cpp"
   )


include_directories("include/AsmNetLib", "include/AsmNetLib/Exceptions")
add_library("AsmNetLib" STATIC ${libsrc} "include/AsmNetLib/Headers.hpp")
set_target_properties("AsmNetLib" PROPERTIES
  #PUBLIC_HEADER "${CMAKE_CURRENT_BINARY_DIR}/config.h")
  PUBLIC_HEADER ${libinclude})

  
if(WIN32)
  target_link_libraries(AsmNetLib CppTinyTools wsock32 ws2_32)
endif()

target_include_directories(AsmNetLib PUBLIC 
                          "${CMAKE_SOURCE_DIR}/CppTinyTools/src"
                          )


install(TARGETS AsmNetLib
  # IMPORTANT: Add the foo library to the "export-set"
  EXPORT AsmNetLibTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/AsmNetLib"
    COMPONENT dev)
