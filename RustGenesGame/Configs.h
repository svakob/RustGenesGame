#pragma once
#include "pch.h"
const char pach[] = "configs.txt";
class Configs {
	std::map<std::string, std::string> data;
public:
	Configs()
	{
		try {
			load();
			
		}
		catch(std::exception& ex){
			data["LengFile"] = "en";
			save();
			
		}
	}
	void save() {
		std::fstream file(pach, std::ios::out);
		for (auto i = data.begin(); i != data.end(); i++) {
			file << (*i).first << ':' << (*i).second << '\n';
		}
		file.close();
	}
	void load() {
		std::fstream file(pach, std::ios::in);
		if (!file.is_open()) { throw std::exception("Not onpend"); }
		std::string line;
		while (std::getline(file, line))
		{
			auto it = std::find(line.begin(), line.end(), ':');
			if (it != line.end()) {
				std::string key(line.begin(), it);
				std::string value(it + 1, line.end());
				data[key] = value;
			}
		}
		file.close();
	}
};