#include "AsmNetwork.h"

using namespace anl;

bool AsmNetwork::initialize()
{
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}

	return true;
}

int AsmNetwork::cleanup()
{
	return WSACleanup();
}
