cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

set(includes 
   "src/TimeClient.hpp" 
   "src/SearchServerTask.hpp" 
   "src/SyncTimeService.hpp" 
)

set(src
   "main.cpp"
   "src/TimeClient.cpp"
   "src/SearchServerTask.cpp"
   "src/SyncTimeService.cpp" 
)


# Add source to this project's executable.
add_executable (TimeClient  ${src})


SET(AsmNetLibPath 
   "${CMAKE_SOURCE_DIR}/AsmNetLib/include" 
   "${CMAKE_SOURCE_DIR}/CppTinyTools/src"
   "${CMAKE_SOURCE_DIR}/TimeProtocol"
   )

target_link_libraries(TimeClient AsmNetLib CppTinyTools TimeProtocol)
include_directories(${AsmNetLibPath} ${includes} "src")
install(TARGETS TimeClient DESTINATION bin)