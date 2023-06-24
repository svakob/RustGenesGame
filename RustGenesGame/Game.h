#pragma once
#include "pch.h"
class Game {

public:
	Game(Configs &configs, LogsSaver &logsaver, Language &language, SaveData &data)
	{
		data.scrap += 5;
		std::cout << data.scrap;
	}
};