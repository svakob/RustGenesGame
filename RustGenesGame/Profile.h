#pragma once
#include "pch.h"

class Profile {

public:
};



struct UserData {
	std::string name;
	std::tm *LastLogin;
};
class Saves {
	const char savedatafilePach[5] = "save";
	std::vector<UserData> data;
	std::fstream file;

public:
	Saves() {
		data.resize(5);
		file.open(savedatafilePach, std::ios::binary | std::ios::in);
		if (file.is_open()) {
			file.read((char*)data.data(), sizeof(UserData) * data.size());
			file.close();
		}
		else {
			file.open(savedatafilePach, std::ios::binary | std::ios::out);
			file.write((char*)data.data(), sizeof(UserData) * data.size());
			file.close();
		}
	}

	bool is_empty() {
		return std::find_if(data.begin(), data.end(), [](UserData& i) {return !i.name.empty(); }) == data.end();
	}
	void mkprofile(std::string name) {
		UserData new_user;
		new_user.name = name;
		data[0] = new_user;
	}
	void save() {
		file.open(savedatafilePach, std::ios::binary | std::ios::out);
		file.write((char*)data.data(), sizeof(UserData) * data.size());
		file.close();
	}
};