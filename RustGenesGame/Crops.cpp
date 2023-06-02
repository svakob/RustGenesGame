#include "pch.h"
#include "Utility.h"
#include "Crops.h"

const char AVAILABLE_GENES[]{ 'G','Y','H','W','X' };
class Crop
{
	
public:
	std::string name;
	char genes[6]{};
	Crop(std::string name)
	{
		this->name = name;
		for (char& i : genes) {
			i = AVAILABLE_GENES[randrange(0, 5)];
		}
	}
};