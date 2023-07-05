#pragma once
#include "pch.h"
class Game {
	unsigned short current_home;
	bool is_open = true;
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
			}
			else if (j == data.homes.size()) {
				current_home = j;
				std::cout << language["game02"] << tab;
				std::string name;
				std::cin >> name;
				std::string size_;
				int size;
				int cost;
				while (true)
				{
					std::cout << language["game10"] << tab;
					std::cin >> size_;
					size = std::stoi(size_);
					if (size > 18) {
						float result = std::pow(size, 1.1);
						cost = std::round(result);
						if (cost <= data.scrap) {
							data.homes.emplace_back(name, size);
							data.scrap -= cost;
							return true;
						}
					}
					else if (size <=18) {
						if (size <= data.scrap) {
							data.homes.emplace_back(name, size);
							data.scrap -= 10;
							return true;
						}
					}
				}
			}
			else if (i == '0') {
				return false;
			}
			else {
				std::cout << language["game04"] << endl;
			}
		}
	}
public:
	Game()
	{
		
	}
	bool start(Configs& configs, LogsSaver& logsaver, Language& language, Saves& save) {
		std::cout << endl << endl;
		
		if (save.current_data.first_time) {
			save.current_data.first_time = false;
			std::cout << language["game01"] << endl;
			save.current_data.scrap = 50;
			save.current_data.seeds["Hemp"] = 10;
			save.current_data.components = 20;
			save.current_data.homes.emplace_back("Home", 18);
			current_home = 0;
			std::cout << language["game02"] << tab;
			std::string name;
			std::cin >> name;
			save.current_data.homes[current_home].name = name;
		}
		while (true)
		{
			if (save.current_data.homes.empty()) {
				save.current_data.homes.emplace_back("Home", 18);
				current_home = 0;
				std::cout << language["game02"] << tab;
				std::string name;
				std::cin >> name;
				save.current_data.homes[current_home].name = name;
			}
			print(language, save.current_data);
			if (!choose_home(language, save.current_data)) {
				return false;
			}
			print(language, save.current_data);
			std::cout << language["save11"] << endl << language["save12"] << endl << language["save13"] << endl << language["save14"] << endl;
			char inputvalue;
			std::cin >> inputvalue;
			if (inputvalue == '1') {
				break;
			}
			else if (inputvalue == '2') {
				save.current_data.homes[current_home].name = getline();
			}
			else if (inputvalue == '3') {
				if (save.current_data.homes.size() > 1) {
					std::cout << language["save15"] << tab;
					char confirmation;
					std::cin >> confirmation;
					if (confirmation == '1') {
						save.current_data.homes.erase(save.current_data.homes.begin() + current_home);
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
		while (true)
		{
			if (save.current_data.homes[current_home].planting_sites.size() == 0) {
				std::cout << language["game05"] << endl;
				std::cout << language["game06"] << tab << save.current_data.homes[current_home].free_space << endl;
				std::cout << language["game07"] << endl;
				std::string size;
				std::cin >> size;
				if (!save.current_data.homes[current_home].craft_and_place_planting(size)) {
					continue;
				}
			}
			save.current_data.homes[current_home].print();
			break; 
		}
		
		return true;
	}
};