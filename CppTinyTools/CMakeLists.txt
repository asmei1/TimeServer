cmake_minimum_required (VERSION 3.10)
project (CppTinyTools VERSION 0.0.1 DESCRIPTION "Simple and tiny cpp tools library for improve programming")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")


add_subdirectory(src)
add_subdirectory(tests)

