//============================================================================
// Name        : WINSIG.cpp
// Author      : jredfox
// Version     : 1.0.0
// Description : Send a CONTROL+C or CONTROL+BREAK or SIGKILL to any CLI APP
//============================================================================

#include <iostream>
#include <windows.h>
#include <wincon.h>
#include <signal.h>

using namespace std;

void sendSignal(unsigned long pid, int signal);

/**
 * argv[0] unsigned long PID
 * argv[1] int SIGNAL
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
    GenerateConsoleCtrlEvent((signal == SIGINT || signal == CTRL_C_EVENT) ? CTRL_C_EVENT : CTRL_BREAK_EVENT, 0);
}
