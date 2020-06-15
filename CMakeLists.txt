cmake_minimum_required (VERSION 3.10)

project ("NTProject") 

# Include sub-projects.
add_subdirectory ("AsmNetLib")
add_subdirectory ("CppTinyTools")
add_subdirectory ("TimeProtocol")
add_subdirectory ("TimeServer")
add_subdirectory ("TimeClient")

