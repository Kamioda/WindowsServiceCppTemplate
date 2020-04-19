#pragma once
#include <stdio.h>
#include <string>

class Console {
private:
	FILE* fp;
public:
	Console();
	~Console();
	void WriteLine(const std::string& str) const;
};