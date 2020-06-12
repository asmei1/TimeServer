cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

set(includes 
   "src/TimeServer.hpp"
   "src/ClientListenerService.hpp"
   "src/ClientHandler.hpp"
)
set(src
   "src/TimeServer.cpp"
   "src/ClientListenerService.cpp"
   "src/ClientHandler.cpp"
   "main.cpp"
)


# Add source to this project's executable.
add_executable (TimeServer ${src})


SET(AsmNetLibPath 
   "${CMAKE_SOURCE_DIR}/AsmNetLib/include" 
   )

target_link_libraries(TimeServer AsmNetLib )
include_directories(${AsmNetLibPath} ${includes} "src")
install(TARGETS TimeServer DESTINATION bin)