#pragma once
#include "pch.h"
class Game {
	unsigned short current_home;
	void print(Language& language, SaveData& data) {
		std::cout << language["game1"] << ":\t" << data.scrap << '\t' << language["game2"] << ":\t" << data.components << endl;
	}
	void print_homes(SaveData& data) {
		for (unsigned short i = 0; i < data.homes.size(); i++) {
			std::cout << std::to_string(i + 1) << tab;
			writelinep(data.homes[i].name);
			std::cout << tab << "space:" << tab << data.homes[i].space << endl;
		}
	}
	bool choose_home(Language& language, SaveData& data) {
		while (true)
		{
			print_homes(data);
			std::cout << language["game03"] << endl;
			char i;
			std::cin >> i;
			int j = std::atoi(&i) - 1;
			if (j >= 0 && j < data.homes.size()) {
				current_home = j;
				return true;
				break;
			}
			else if (j == '-1') {

			}
			else {
				std::cout << language["game04"] << endl;
			}
		}
	}
public:
	Game(Configs &configs, LogsSaver &logsaver, Language &language, SaveData &data)
	{
		std::cout << endl << endl;
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
			print(language, data);
			
			std::cout << language["game05"] << endl;
			std::cout << language["game06"] << tab << data.homes[current_home].free_space << endl;
			std::cout << language["game07"] << endl;
			std::string size;
			std::cin >> size;
			if (size != "0") {
				data.homes[current_home].craft_and_place_planting(size);
			}
		}
		while (true)
		{
			if (data.homes.empty()) {
				data.homes.emplace_back("Home", 18);
				current_home = 0;
				std::cout << language["game02"] << tab;
				std::string name;
				std::cin >> name;
				data.homes[current_home].name = name;
			}
			print(language, data);
			choose_home(language, data);
			std::cout << language["save11"] << endl << language["save12"] << endl << language["save13"] << endl << language["save14"] << endl;
			char inputvalue;
			std::cin >> inputvalue;
			if (inputvalue == '1') {
				break;
			}
			else if (inputvalue == '2') {
				data.homes[current_home].name = getline();
			}
			else if (inputvalue == '3') {
				if (data.homes.size() > 1) {
					std::cout << language["save15"] << tab;
					char confirmation;
					std::cin >> confirmation;
					if (confirmation == '1') {
						data.homes.erase(data.homes.begin() + current_home);
					}
				}
				else
				{
					std::cout << language["game09"] << endl;
				}
			}
			else if (inputvalue == '0') {
				continue;
			}
		}
	}
};