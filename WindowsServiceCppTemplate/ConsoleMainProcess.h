#pragma once
#include "CommandLineManager.h"
#include <Windows.h>
#include <string>
#include <vector>

/*
	Console_CommandLineManager
	CommandLineManagerA
		Command line argument type						：std::vector<std::string>
		Return value of AlignCmdLineStrType function	: std::string
	CommandLineManagerw
		Command line argument type						：std::vector<std::wtring>
		Return value of AlignCmdLineStrType function	: std::wtring

*/

namespace Console_CommandLineManager = CommandLineManagerA;

void Console_MainProcess(HINSTANCE hInstance, const Console_CommandLineManager::CommandLineType& CommandLines, int nCmdShow);
