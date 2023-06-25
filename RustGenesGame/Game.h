#pragma once
#include "pch.h"
class Game {
	void print(Language& language, SaveData& data) {
		std::cout << language["game1"] << ":\t" << data.scrap << '\t' << language["game2"] << ":\t" << data.components << endl;
	}
public:
	Game(Configs &configs, LogsSaver &logsaver, Language &language, SaveData &data)
	{
		std::cout << endl << endl << endl;
		if (data.first_time) {
			data.first_time = false;
			std::cout << language["game01"] << endl;
			data.scrap = 50;
			data.seeds["Hemp"] = 10;
			data.components = 20;
		}
		print(language, data);

	}
};