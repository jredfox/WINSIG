# WINSIG
 Send Windows Signals as though your on POSIX to CLI Apps CONTROL+C & CONTROL+BREAK. If you need anything more extensive then this and windows terminate please use PIDIA library. We can't send CONTROL_CLOSE_EVENT due to the limitions of windows console signals api itself.
 
 Using WINSIG
 ```
 WINSIG.exe "PID" "<CODE>"
 ```
PID = DWORD(unsigned long) `process id`  
CODE = int signal `SIGINT, CTRL_C_EVENT, SIGTERM, CONTROL_BREAK_EVENT`
