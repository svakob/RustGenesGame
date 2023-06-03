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
		/*plant.reserve(height);
		for (unsigned short i = 0; i < height; i++) {
			plant.emplace_back(std::vector<Crop*>(width));
			for (unsigned short j = 0; j < height; j++) {
				plant[i][j] = nullptr;
			}
		}*/
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
					std::cout << '0' << '\t';
				}
			}
			std::cout << '\n';
		}
	}
};