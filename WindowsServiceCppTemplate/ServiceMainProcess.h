#pragma once
#include "CommandLineManager.h"

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
	Service_CommandLineManager::CommandLineStringType ModuleFileDirectory;
	Service_CommandLineManager::CommandLineStringType ChangeFullPath(const Service_CommandLineManager::CommandLineStringType& Path) const noexcept;
public:
	virtual void Service_MainProcess() = 0;
public:
	// Arguments
	// args                         : Argument of GetServiceProcessInstance function
	// CurrentDirectoryIsModulePath : Flag of moving current directory to directory module file exists. If this parameter is false, current directory is C:\Windows\System32
	ServiceProcess(const Service_CommandLineManager::CommandLineType& args, const bool CurrentDirectoryIsModulePath = false);
};

ServiceProcess* GetServiceProcessInstance(const Service_CommandLineManager::CommandLineType& args);
