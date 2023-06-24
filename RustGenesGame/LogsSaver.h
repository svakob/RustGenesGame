#pragma once
#include "pch.h"
#include "Configs.h"

class LogsSaver
{
	const char pach[9] = "logs.txt";
	std::fstream file;
	unsigned short loglvl;
public:
	LogsSaver(Configs &configs) {
		loglvl = std::stoul(configs["Logs"]);
		if (loglvl != 0)
		{
			file.open(pach, std::ios::app);
		}
	}
	~LogsSaver() {
		file.close();
	}


	void log(unsigned short lvl, const char *importance, const char *message) {
		if (lvl <= loglvl){
			std::time_t now = std::time(0);
			std::tm time;
			localtime_s(&time, &now);
			char datatime[28];
			std::strftime(datatime, sizeof(datatime), "[%d.%m.%Y][%H:%M:%S]", &time);
			const unsigned short size = sizeof(datatime) + sizeof(importance) + sizeof(message) + 4;
			std::string strtolog;
			strtolog.reserve(size);
			strtolog = std::string(datatime) + "[" + std::string(importance) + "][" + std::string(message) + "]\n";
			file << strtolog;
		}
	}
};
