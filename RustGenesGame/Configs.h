#pragma once
#include "pch.h"

class Configs {
	const char pach[12] = "configs.txt";
	const std::list<std::pair<std::string, std::string>> base_data{{"LengFile", "en"}, { "Logs", "0" }};
	std::map<std::string, std::string> data;
	void if_not_defined_default() {
		for (auto& i : base_data) {
			if (std::find_if(data.begin(), data.end(), [i](const std::pair<std::string, std::string> &j) { return j.first == i.first; }) == data.end()) {
				data[i.first] = i.second;
				save(i);
			}
		}
	}
public:
	Configs()
	{
		try {
			load();
			if_not_defined_default();
		}
		catch(...){
			if_not_defined_default();
		}
	}
	void save() {
		std::fstream file(pach, std::ios::out);
		for (auto i = data.begin(); i != data.end(); i++) {
			file << (*i).first << ':' << (*i).second << '\n';
		}
		file.close();
	}
	void save(const std::pair<std::string, std::string> &SingleData) {
		std::fstream file(pach, std::ios::app);
		file << SingleData.first << ':' << SingleData.second << '\n';
		file.close();
	}
	void save(const char &str) {
		std::fstream file(pach, std::ios::app);
		file << '\n';
		file.close();
	}
	void load() {
		std::fstream file(pach, std::ios::in);
		if (!file.is_open()) { throw; }
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
	void Print() {
		for (auto& i : data) {
			std::cout << i.first << ":" << i.second << '\n';
		}
	}
};