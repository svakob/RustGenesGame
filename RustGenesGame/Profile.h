#pragma once
#include "pch.h"

class Profile {

public:
};

const char savedatafilePach[5] = "save";

struct UserData {
	std::string name;
	std::tm LastLogin;
};
class Saves {
	unsigned short size = 5;
	std::fstream file;
	std::vector<UserData> data;
public:
	Saves()
	{
		data.reserve(5);
		file.open(savedatafilePach, std::ios::binary | std::ios::in);
		if (file.is_open()) {
			file.read(reinterpret_cast<char*>(&size), sizeof(size));
			file.close();
		}
		else
		{
			file.open(savedatafilePach, std::ios::binary | std::ios::out);
			file.write(reinterpret_cast<const char*>(data.data()), sizeof(int) * size);
			file.close();
		}
	}
	bool is_empty() {
		return data.empty();
	}
};