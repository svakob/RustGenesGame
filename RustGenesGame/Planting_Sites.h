#pragma once
#include "pch.h"

#include "Crops.h"

class Planting_Site
{
	std::vector<std::vector<Crop*>> plant;
	unsigned short height;
	unsigned short width;
public:
	Planting_Site(std::string size)
	{
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
		plant.assign(height, std::vector<Crop*>(width, nullptr));
	}
	~Planting_Site()
	{
		plant.clear();
	}
	void Print() {
		for (auto& i : plant)
		{
			for (auto& j : i) {
				if (j != nullptr)
				{
					std::cout << j->genes << '\t';
				}
				else
				{
					std::cout << u8"  ø   " << '\t';
				}
			}
			std::cout << endl;
		}
	}
};