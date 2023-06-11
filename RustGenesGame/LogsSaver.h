#pragma once
#include "pch.h"

class LogsSaver
{
	const char pach[9] = "logs.txt";
	std::fstream file;
public:
	LogsSaver() {
		file.open(pach, std::ios::app);
	}
	~LogsSaver() {
		file.close();
	}
};
