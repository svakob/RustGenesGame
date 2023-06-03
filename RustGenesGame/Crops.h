#pragma once
#include "pch.h"
#include "Utility.h"

const char AVAILABLE_GENES[]{ 'G','Y','H','W','X' };
class Crop
{

public:
	std::string name;
	char genes[7]{};
	Crop(std::string name)
	{
		this->name = name;
		for (unsigned short i = 0; i < 6; i++) {
			genes[i] = AVAILABLE_GENES[randrange(0, 4)];
		}
		genes[6] = '\0';
	}
};