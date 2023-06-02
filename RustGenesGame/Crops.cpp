#include "pch.h"
#include "Utility.h"
#include "Crops.h"

const char AVAILABLE_GENES[]{ 'G','Y','H','W','X' };
class Crop
{
	std::string name;
	char genes[6]{};
public:
	Crop(std::string name)
	{
		this->name = name;
		for (char& i : genes) {
			i = AVAILABLE_GENES[randrange(0, 5)];
		}
	}
};