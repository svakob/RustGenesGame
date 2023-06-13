#pragma once
#include "pch.h"
#include "Configs.h"
class Language {
	std::string pach;
	const std::list<std::pair<std::string, std::string>> base_data{
		{ "init1", "presents" }, 
		{ "init2", "Loading..." },
		{ "save1", "It looks like you are running this game for the first time."},
		{ "save2", "Okay, let's start." },
		{ "save3", "Welcome back." }
	};
	unsigned short if_not_defined_default() {
		unsigned short count = 0;
		for (auto& i : base_data) {
			if (std::find_if(data.begin(), data.end(), [i](const std::pair<std::string, std::string>& j) { return j.first == i.first; }) == data.end()) {
				data[i.first] = i.second;
				count++;
			}
		}
		return count;
	}
	bool load() {
		std::fstream file(pach, std::ios::in);
		if (!file.is_open()) { return false; }
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
		return false;
	}
public:
	std::unordered_map<std::string, std::string> data;
	Language(Configs configs)
	{
		pach = (*configs.data.find("LengFile")).second;
		load();
		if_not_defined_default();
	}
};