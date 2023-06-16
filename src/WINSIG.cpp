//============================================================================
// Name        : WINSIG.cpp
// Author      : jredfox
// Version     : 1.0.0
// Description : Send a CONTROL+C(SIGINT(2) or 0) or CONTROL+BREAK(1) signal to the CLI Process Group
//============================================================================

#include <iostream>
#include <windows.h>
#include <wincon.h>
#include <signal.h>
#include <process.h>
#include <vector>

using namespace std;

bool sendSignal(unsigned long pid, int signal);

/**
 * NOTE: in C++ argv[0] is equal to the executable's name usually
 * argv[1] unsigned long PID
 * argv[2] int SIGNAL
 */
int main(int argc, char *argv[])
{
	unsigned long pid = stoul(argv[1]);
	int signal = std::atoi(argv[2]);
	int r = sendSignal(pid, signal);
	return (r ? 0 : -1);//if we failed return negative 1
}

/**
 * do not call this on the same process it's internal
 */
bool sendSignal(unsigned long pid, int signal)
{
    FreeConsole();
	AttachConsole(pid);
	SetConsoleCtrlHandler(NULL, true);//disables CONTROL+C for our process so we don't accidently close ourselves
    return GenerateConsoleCtrlEvent((signal == CTRL_BREAK_EVENT || signal == SIGBREAK) ? CTRL_BREAK_EVENT : CTRL_C_EVENT, 0);
}
