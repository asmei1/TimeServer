cmake_minimum_required (VERSION 3.10)
project (TimeProtocol)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_library(TimeProtocol STATIC 
   "TimeProtocol.cpp"
   )
    
target_link_libraries(TimeProtocol AsmNetLib CppTinyTools)

target_include_directories(TimeProtocol PUBLIC 
   "${CMAKE_SOURCE_DIR}/AsmNetLib/include" 
   "${CMAKE_SOURCE_DIR}/CppTinyTools/src"
) 
