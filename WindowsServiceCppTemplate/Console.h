#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>

class Console {
private:
	FILE* fp;
	HANDLE hStdOutput;
public:
	Console();
	~Console();
	DWORD Write(const std::string& str, const bool Pause = false) const;
	DWORD WriteLine(const std::string& str, const bool Pause = false) const;
};
