#pragma once
#include "pch.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>

static const unsigned short version;

struct UserData {
    std::string name;
    time_t LastLogin;
    unsigned short version;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& name;
        ar& LastLogin;
        ar& version;
    }
};

BOOST_CLASS_VERSION(UserData, 0)

class Saves {
    const char savedatafilePath[5] = "save";
    std::vector<UserData> data;
    std::fstream file;

public:
    Saves() {
        data.resize(5);
        load();
    }

    bool is_empty() {
        return std::find_if(data.begin(), data.end(), [](UserData& i) { return !i.name.empty(); }) == data.end();
    }
    void mkprofile(std::string name) {
        UserData new_user;
        new_user.name = name;
        new_user.LastLogin = time(nullptr);
        data[0] = new_user;
    }
    void save() {
        std::ofstream ofs(savedatafilePath);
        boost::archive::text_oarchive oa(ofs);
        oa << data;
        ofs.close();
    }
    void load() {
        std::ifstream ifs(savedatafilePath);
        if (ifs.is_open()) {
            boost::archive::text_iarchive ia(ifs);
            ia >> data;
            ifs.close();
        }
        else {
            save();
        }
    }
};