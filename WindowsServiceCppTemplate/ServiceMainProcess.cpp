#include "ServiceStatus.h"
#include "ServiceMainProcess.h"

ServiceProcess::ServiceProcess(const Service_CommandLineManager::CommandLineType& args)
	: Argv(args) { 
	SvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	SvcStatus.dwCurrentState = SERVICE_START_PENDING;
	SvcStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_STOP;
	SvcStatus.dwWin32ExitCode = NO_ERROR;
	SvcStatus.dwServiceSpecificExitCode = 0;
	SvcStatus.dwCheckPoint = 0;
	SvcStatus.dwWaitHint = 2000;
	SetServiceStatusInfo();
}
