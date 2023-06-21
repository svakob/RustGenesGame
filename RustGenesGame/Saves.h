#pragma once
#include "pch.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>

#define endl '\n'

const unsigned short version = 1;

struct SaveData {

};

struct SaveInfo {
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

BOOST_CLASS_VERSION(SaveInfo, 1)

class Saves {
    const std::string savedatafilePath = "save/";
    std::vector<SaveInfo> data{5};
    unsigned short current_slot = 0;

public:
    Saves() {
        load();
    }
    ~Saves()
    {
        if (current_slot != 50) {
            logout();
        }
    }
    bool is_empty() {
        return std::find_if(data.begin(), data.end(), [](SaveInfo& i) { return !i.name.empty(); }) == data.end();
    }
    void ifndeff_folder() {
        if (!std::filesystem::exists(savedatafilePath)) {
            std::filesystem::create_directory(savedatafilePath);
        }
    }
    void mkprofile(std::string &name) {
        data[current_slot].name = name;
        data[current_slot].Lastlogging = time(nullptr);
        data[current_slot].version = version;
        current_slot = current_slot;
    }
    void save() {
        ifndeff_folder();
        std::ofstream ofs;
        for (unsigned short i = 0; i < 5; i++) {
            if (data[i].name != "") {
                ofs.open(savedatafilePath + "save" + std::to_string(i + 1) + ".si");
                if (ofs.is_open()) {
                    boost::archive::binary_oarchive oa(ofs);
                    oa << data[i];
                    ofs.close();
                }
            }
        }
    }
    void load() {
        std::ifstream ifs;
        for (unsigned short i = 0; i < 5; i++) {
            ifs.open(savedatafilePath + "save" + std::to_string(i + 1) + ".si");
            if (ifs.is_open())
            {
                boost::archive::binary_iarchive ia(ifs);
                ia >> data[i];
                ifs.close();
            }
        }
    }
    void login(unsigned short slot) {
        current_slot = slot;
    }
    void logout() {
        data[current_slot].Lastlogging = time(nullptr);
        save();
        current_slot = 50;
    }
    bool is_empty_current() {
        return data[current_slot].name.empty();
    }
    void print() {
        std::cout << "N\tname\tago\tversion\n";
        for (unsigned short i = 0; i < 5;i++) {
            if (data[i].name != "") {
                writeline(std::to_string(i + 1) + ":\t" + data[i].name + "\t" + data[i].LastloggingDiff() + "\t" + std::to_string(data[i].version) + endl);
            }
            else {
                std::cout << i + 1 << ":\tNone\n";
            }
        }
    }
};