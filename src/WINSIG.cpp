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

using namespace std;

void sendSignal(unsigned long pid, int signal);

/**
 * NOTE: in C++ argv[0] is equal to the executable's name usually
 * argv[1] unsigned long PID
 * argv[2] int SIGNAL
 */
int main(int argc, char *argv[])
{
	unsigned long pid = stoul(argv[1]);
	int signal = std::atoi(argv[2]);
	sendSignal(pid, signal);
}

/**
 * do not call this on the same process it's internal
 */
void sendSignal(unsigned long pid, int signal)
{
	//SIGKILL is always 9
	if(signal == 9)
	{
		const auto explorer = OpenProcess(PROCESS_TERMINATE, false, pid);
		TerminateProcess(explorer, 1);
		CloseHandle(explorer);
		return;
	}
    FreeConsole();
	AttachConsole(pid);
    GenerateConsoleCtrlEvent((signal == CTRL_BREAK_EVENT || signal == SIGBREAK) ? CTRL_BREAK_EVENT : CTRL_C_EVENT, 0);
}
