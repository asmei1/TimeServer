cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

# Add source to this project's executable.
add_executable (TimeClient "main.cpp" )

SET(AsmNetLibPath "${CMAKE_SOURCE_DIR}/AsmNetLib/include")

include_directories(${AsmNetLibPath})
target_link_libraries(TimeClient AsmNetLib)
install(TARGETS TimeServer DESTINATION bin)