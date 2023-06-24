#pragma once
#include "pch.h"

#define endl '\n'

class Configs {
	const char pach[12] = "configs.cfg";
	const std::list<std::pair<std::string, std::string>> default_data{{"LengFile", "en"}, { "Logs", "0" }};
	std::unordered_map<std::string, std::string> data;

	unsigned short if_not_defined_default() {
		unsigned short count = 0;
		for (auto& i : default_data) {
			if (std::find_if(data.begin(), data.end(), [i](const std::pair<std::string, std::string> &j) { return j.first == i.first; }) == data.end()) {
				data[i.first] = i.second;
				save(i);
				count++;
			}
		}
		return count;
	}
public:
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
	std::string& operator[](std::string & value) {
		return data[value];
	}
	std::string& operator[](const char* value) {
		return data[value];
	}
	void save() {
		std::fstream file(pach, std::ios::out | std::ios::trunc);
		for (auto i = data.begin(); i != data.end(); i++) {
			file << (*i).first << ':' << (*i).second << endl;
		}
		file.close();
	}
	void save(const std::pair<std::string, std::string> &SingleData) {
		std::fstream file(pach, std::ios::app);
		file << SingleData.first << ':' << SingleData.second << endl;
		file.close();
	}
	void save(const char &str) {
		std::fstream file(pach, std::ios::app);
		file << endl;
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
			std::cout << i.first << ":" << i.second << endl;
		}
	}
};