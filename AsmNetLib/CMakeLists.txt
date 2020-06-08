cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

set(libinclude 
   #"include/AsmNetLib/AsmNetLib.hpp"
   "include/AsmNetLib/Types.hpp"
   "include/AsmNetLib/AsmNetwork.hpp"
   "include/AsmNetLib/SocketInternals.hpp"
   "include/AsmNetLib/MulticastSocket.hpp"
   "include/AsmNetLib/UDPSocket.hpp"
   "include/AsmNetLib/TCPSocket.hpp"
   "include/AsmNetLib/TCPServerSocket.hpp"
   "include/AsmNetLib/InetAddress.hpp"
   "include/AsmNetLib/Exceptions/SocketException.hpp"
   "include/AsmNetLib/Exceptions/BindException.hpp"
   "include/AsmNetLib/Exceptions/SocketCreateException.hpp"
   "include/AsmNetLib/Exceptions/TimeoutException.hpp"
   "include/AsmNetLib/Exceptions/DatagramSizeOutOfRangeException.hpp"
   )

set(libsrc 
   "src/AsmNetLib/AsmNetwork.cpp"
   "src/AsmNetLib/SocketInternals.cpp"
   "src/AsmNetLib/MulticastSocket.cpp"
   "src/AsmNetLib/TCPServerSocket.cpp"
   "src/AsmNetLib/TCPSocket.cpp"
   "src/AsmNetLib/UDPSocket.cpp"
   "src/AsmNetLib/Helper.cpp"
   )


include_directories("include/AsmNetLib", "include/AsmNetLib/Exceptions")
add_library("AsmNetLib" STATIC ${libsrc})
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
