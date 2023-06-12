#pragma once
#include "pch.h"

class Configs {
	const char pach[12] = "configs.txt";
	const std::list<std::pair<std::string, std::string>> base_data{{"LengFile", "en"}, { "Logs", "0" }};
	
	unsigned short if_not_defined_default() {
		unsigned short count = 0;
		for (auto& i : base_data) {
			if (std::find_if(data.begin(), data.end(), [i](const std::pair<std::string, std::string> &j) { return j.first == i.first; }) == data.end()) {
				data[i.first] = i.second;
				save(i);
				count++;
			}
		}
		return count;
	}
public:
	std::map<std::string, std::string> data;
	Configs()
	{
		if (load()){
			if_not_defined_default();
		}
		else{
			if_not_defined_default();
		}
	}
	~Configs()
	{
		save();
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
	void Print() {
		for (auto& i : data) {
			std::cout << i.first << ":" << i.second << '\n';
		}
	}
};