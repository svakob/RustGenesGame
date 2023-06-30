#pragma once
#include "pch.h"
class Home {
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version) {
        ar& name;
        ar& space;
        ar& planting_sites;
        free_space = space;
        if (!planting_sites.empty()) {
            for (auto& i : planting_sites) {
                free_space -= i.get_space();
            }
        }
    }
public:
    std::string name;
    unsigned int space;
    std::vector<Planting_Site> planting_sites;

    unsigned int free_space;

    Home()
    {
        name = "None";
        space = 0;
        free_space = 0;
    }
    Home(std::string name, unsigned int space)
    {
        this->name = name;
        this->space = space;
        free_space = space;
        if (!planting_sites.empty()) {
            for (auto& i : planting_sites) {
                free_space -= i.get_space();
            }
        }
    }
    void craft_and_place_planting(std::string size) {
        std::string Sheight;
        std::string Swidth;
        auto x = std::find(size.begin(), size.end(), 'x');
        std::copy(size.begin(), x, std::back_inserter(Sheight));
        std::copy(x + 1, size.end(), std::back_inserter(Swidth));
        unsigned short height = std::stoi(Sheight);
        unsigned short width = std::stoi(Swidth);
        if (height <= 0 || width <= 0) {
            throw std::invalid_argument("Invalid size");
        }
        unsigned short new_space = height * width;
        if (free_space >= new_space) {
            planting_sites.emplace_back(height, width);
        }
    }
};