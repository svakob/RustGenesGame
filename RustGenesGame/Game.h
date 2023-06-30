#pragma once
#include "pch.h"
class Game {
	unsigned short current_home;
	void print(Language& language, SaveData& data) {
		std::cout << language["game1"] << ":\t" << data.scrap << '\t' << language["game2"] << ":\t" << data.components << endl;
	}
	void print_homes(SaveData& data) {
		for (unsigned short i = 0; i < data.homes.size(); i++) {
			std::cout << std::to_string(i + 1) << tab << data.homes[i].name << "space:" << tab << data.homes[i].space << endl;
		}
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
			data.homes.emplace_back("Home", 18);
			current_home = 0;
			std::cout << language["game02"] << tab;
			std::string name;
			std::cin >> name;
			data.homes[current_home].name = name;
		}
		if (data.homes.size() > 0) {
			while (true)
			{
				print_homes(data);
				std::cout << language["game03"] << endl;
				char i;
				std::cin >> i;
				int j = std::atoi(&i)-1;
				if (j >= 0 && j < data.homes.size()) {
					current_home = j;
					break;
				}
				else {
					std::cout << language["game04"] << endl;
				}
			}
		}
		print(language, data);
		if (data.homes[current_home].planting_sites.empty()) {
			std::cout << language["game05"] << endl;
		}
		

	}
};