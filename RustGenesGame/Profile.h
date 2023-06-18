#pragma once
#include "pch.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>

const unsigned short version = 1;

class Profile {

};

struct UserData {
    std::string name;
    time_t Lastlogging;
    unsigned short version;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& name;
        ar& Lastlogging;
        ar& this->version;
    }
    std::string LastloggingDiff() {
        std::chrono::system_clock::time_point lastlogging = std::chrono::system_clock::from_time_t(Lastlogging);
        std::chrono::system_clock::duration diff = std::chrono::system_clock::now() - lastlogging;
        if (std::chrono::duration_cast<std::chrono::minutes>(diff).count() < 60){
            return std::to_string(std::chrono::duration_cast<std::chrono::minutes>(diff).count())+"m";
        }
        else if (std::chrono::duration_cast<std::chrono::hours>(diff).count() < 60)
        {
            return std::to_string(std::chrono::duration_cast<std::chrono::hours>(diff).count())+"h";
        }
        else {
            return std::to_string(std::chrono::duration_cast<std::chrono::hours>(diff).count()%24)+"d";
        }
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
    void mkprofile(std::string name, unsigned short slot = 0) {
        UserData new_user;
        new_user.name = name;
        new_user.Lastlogging = time(nullptr);
        new_user.version = version;
        data[slot] = new_user;
    }
    void save() {
        std::ofstream ofs(savedatafilePath);
        boost::archive::binary_oarchive oa(ofs);
        oa << data;
        ofs.close();
    }
    void load() {
        std::ifstream ifs(savedatafilePath);
        if (ifs.is_open()) {
            boost::archive::binary_iarchive ia(ifs);
            ia >> data;
            ifs.close();
        }
        else {
            save();
        }
    }
    UserData* login(const unsigned short soket) {
        return data.data() + soket;
    }
    void print() {
        std::cout << u8"¹\tname\tago\tvercion\n";
        for (unsigned short i = 0; i < 5;i++) {
            if (data[i].name != "") {
                std::cout << i + 1 << ":\t" << data[i].name << "\t" << data[i].LastloggingDiff() << "\t" << data[i].version << "\n";
            }
            else {
                std::cout << i + 1 << ":\tNone\n";
            }
        }
    }
};