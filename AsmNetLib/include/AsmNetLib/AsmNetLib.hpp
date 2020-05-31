#pragma once
//#pragma comment(lib,"ws2_32.lib") //Winsock Library

#include "NetworkHeaders.hpp"
#include "ILogger.hpp"
#include "AsmNetwork.h"
#include "MulticastSocket.h"
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "TCPServerSocket.h"
#include "InetAddress.h"
#include "BasicLogger.hpp"

#include "Exceptions/BindException.h"
#include "Exceptions/TCPServerSocketCreateException.h"
#include "Exceptions/TimeoutException.h"
#include "Exceptions/DatagramSizeOutOfRangeException.h"
