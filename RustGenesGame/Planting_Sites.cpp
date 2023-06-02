#include "pch.h"
#include "Planting_Sites.h"
#include "Crops.cpp"

class Planting_Site
{
	std::vector<std::vector<Crop>> plant;
public:
	Planting_Site(std::string size)
	{
		unsigned short height;
		unsigned short width;
		{
			std::string Sheight;
			std::string Swidth;
			auto x = std::find(size.begin(), size.end(), 'x');
			std::copy(size.begin(), x, std::back_inserter(Sheight));
			std::copy(x + 1, size.end(), std::back_inserter(Swidth));
			height = std::stoi(Sheight);
			width = std::stoi(Swidth);
			if (height <= 0 || width <= 0) {
				throw std::invalid_argument("Invalid size");
			}
		}
		plant.reserve(height);
		std::for_each(plant.begin(), plant.end(), [width](std::vector<Crop> i) {i.reserve(width); });
	}
	void Print() {
		std::for_each(plant.begin(), plant.end(), [](std::vector<Crop> i) {std::for_each(i.begin(), i.end(), [](Crop k) {std::cout << k.genes << '\t'; }); std::cout << '\n'; });
	}
};