#pragma once
#include "CommandLineManager.h"
#include <Windows.h>

/*
	Service_CommandLineManager
	CommandLineManagerA
		Command line argument type						：std::vector<std::string>
		Return value of AlignCmdLineStrType function	: std::string
	CommandLineManagerw
		Command line argument type						：std::vector<std::wtring>
		Return value of AlignCmdLineStrType function	: std::wtring

*/

namespace Service_CommandLineManager = CommandLineManagerA;

class ServiceProcess {
protected:
	Service_CommandLineManager::CommandLineType Argv;
public:
	virtual void Service_MainProcess() = 0;
public:
	ServiceProcess(const Service_CommandLineManager::CommandLineType& args);
};

ServiceProcess* GetServiceProcessInstance(const Service_CommandLineManager::CommandLineType& args);
