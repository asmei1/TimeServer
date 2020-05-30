// TimeServer.cpp : Defines the entry point for the application.
//

#include <iostream>


#include "AsmNetLib/Helper.hpp"

int main()
{
	std::cout << "Hello CMake." << anl::chkNumber("1")  << std::endl;
	return 0;
}
