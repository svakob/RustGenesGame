#pragma once
#include "pch.h"

class Profile {

public:
};



struct UserData {
	std::string name;
	std::tm LastLogin;
};
class Saves {
	const char savedatafilePach[5] = "save";
	const static unsigned short size = 5;
	std::array<UserData, size> data;
	std::fstream file;

public:
	Saves() {
		file.open(savedatafilePach, std::ios::binary | std::ios::in);
		if (file.is_open()) {
			
			file.close();
		}
		else {
			file.open(savedatafilePach, std::ios::binary | std::ios::out);
			file.write(reinterpret_cast<const char*>(data.data()), sizeof(UserData) * size);
			file.close();
		}
	}

	bool is_empty() {
		return std::find_if(data.begin(), data.end(), [](UserData& i) {return !i.name.empty(); }) == data.end();
	}
	void mkprofile(std::string name) {
		data[0].name = name;
	}
	void save() {
		file.open(savedatafilePach, std::ios::binary | std::ios::out);
		file.write(reinterpret_cast<const char*>(data.data()), sizeof(UserData) * size);
		file.close();
	}
};