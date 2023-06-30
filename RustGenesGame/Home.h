#pragma once
#include "pch.h"
class Home {
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version) {
        ar& name;
        ar& space;
        ar& planting_sites;
    }
public:
    std::string name;
    unsigned int space;
    std::vector<Planting_Site> planting_sites;
    Home()
    {
        name = "None";
        space = 0;
    }
    Home(std::string name, unsigned int space)
    {
        this->name = name;
        this->space = space;
    }
};