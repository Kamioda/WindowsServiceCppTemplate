#pragma once
#include <string>
#include <vector>
namespace CommandLine {
	namespace CharArg {
		std::vector<std::string> GetCommandLineArg(const char* lpCmdLine);
		std::vector<std::string> GetCommandLineArg(const wchar_t* lpCmdLine);
		std::string AlignCmdLineStrType(const std::string& str);
		std::string AlignCmdLineStrType(const std::wstring& str);
		std::vector<std::string> GetCommandLineArg(const std::vector<std::string>& args);
		std::vector<std::string> GetCommandLineArg(const std::vector<std::wstring>& args);
		typedef std::string CommandLineStringType;
		typedef std::vector<std::string> CommandLineType;
	}
	namespace WCharArg {
		std::vector<std::wstring> GetCommandLineArg(const char* lpCmdLine);
		std::vector<std::wstring> GetCommandLineArg(const wchar_t* lpCmdLine);
		std::wstring AlignCmdLineStrType(const std::string& str);
		std::wstring AlignCmdLineStrType(const std::wstring& str);
		std::vector<std::wstring> GetCommandLineArg(const std::vector<std::string>& args);
		std::vector<std::wstring> GetCommandLineArg(const std::vector<std::wstring>& args);
		typedef std::wstring CommandLineStringType;
		typedef std::vector<std::wstring> CommandLineType;
	}
}

namespace CommandLineManagerA = CommandLine::CharArg;
namespace CommandLineManagerW = CommandLine::WCharArg;
