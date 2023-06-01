#include "pch.h"
#include "Crops.h"

int randrange(int minimum_number, int max_number) {
	return (rand() % (max_number + 1 - minimum_number)) + minimum_number;
}
int randrange(int max_number) {
	return (rand() % (max_number + 1));
}

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