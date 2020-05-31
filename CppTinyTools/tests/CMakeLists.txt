project (CppTinyToolsTests)
add_executable (CppTinyToolsTests "ParserTests.cpp")
target_link_libraries(CppTinyToolsTests PUBLIC CppTinyTools)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(CppTinyToolsTests PUBLIC 
                          "${CMAKE_SOURCE_DIR}"
                          "${CMAKE_SOURCE_DIR}/src"
                          )
                           