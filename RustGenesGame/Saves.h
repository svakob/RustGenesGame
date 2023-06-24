#pragma once
#include "pch.h"
#include "Crops.h"
#include "Planting_Sites.h"

#define endl '\n'

const unsigned short version = 1;

struct SaveData {
    unsigned short scrap;
    unsigned short seeds;
    std::vector<Crop> clons;
    std::vector<Planting_Site> planting_sites;
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version) {
        ar& scrap;
        ar& seeds;
        ar& clons;
        ar& planting_sites;
    }
};

BOOST_CLASS_VERSION(SaveData, 1)

struct SaveInfo {
    std::string name;
    time_t Lastlogging;
    unsigned short version;
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version) {
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
        else if (std::chrono::duration_cast<std::chrono::hours>(diff).count() < 24)
        {
            return std::to_string(std::chrono::duration_cast<std::chrono::hours>(diff).count())+"h";
        }
        else {
            return std::to_string(std::chrono::duration_cast<std::chrono::hours>(diff).count()/24)+"d";
        }
    }
};

BOOST_CLASS_VERSION(SaveInfo, 1)

class Saves {
    const std::string savedatafilePath = "save/";
    std::vector<SaveInfo> data{5};
    unsigned short current_slot = 0;
    bool loaded = false;

    SaveData current_data;

    void ifndeff_folder() {
        if (!std::filesystem::exists(savedatafilePath)) {
            std::filesystem::create_directory(savedatafilePath);
        }
    }
    void if_not_all_data_thear_delete() {
        for (int i = 0; i < 5; i++) {
            if (data[i].name != "")
            {
                std::ifstream ifs(savedatafilePath + "save" + std::to_string(i + 1) + ".sd");
                if (!ifs.is_open()) {
                    data[i].name = "";
                    std::remove((savedatafilePath + "save" + std::to_string(i + 1) + ".si").data());
                }
            }
            else {
                std::ifstream ifs(savedatafilePath + "save" + std::to_string(i + 1) + ".sd");
                if (ifs.is_open()) {
                    data[i].name = "Not defined";
                    data[i].version = version;
                    data[i].Lastlogging = time(nullptr);
                    save();
                    qincorrect_names.push(i+1);
                }
            }
        }
    }


public:
    std::queue<unsigned short, std::list<unsigned short>> qincorrect_names;

    Saves() {
        load();
        if_not_all_data_thear_delete();
    }
    ~Saves()
    {
        if (current_slot != 5 && loaded) {
            logout();
        }
    }
    bool is_empty() {
        return std::find_if(data.begin(), data.end(), [](SaveInfo& i) { return !i.name.empty(); }) == data.end();
    }
    
    void mkprofile(std::string &name) {
        data[current_slot].name = name;
        data[current_slot].Lastlogging = time(nullptr);
        data[current_slot].version = version;
        current_data.scrap = 0;
        current_data.seeds = 0;
        save_data();
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
    
    void save_data() {
        ifndeff_folder();
        std::ofstream ofs(savedatafilePath + "save" + std::to_string(current_slot + 1) + ".sd");
        boost::archive::binary_oarchive oa(ofs);
        oa << current_data;
        ofs.close();
    }
    void load_data() {
        std::ifstream ifs(savedatafilePath + "save" + std::to_string(current_slot + 1) + ".sd");
        if (ifs.is_open()) {
            boost::archive::binary_iarchive ia(ifs);
            ia >> current_data;
            ifs.close();
        }
    }
    void login(unsigned short slot) {
        current_slot = slot;
    }
    void login(bool load, int) {
        loaded = load;
    }
    void logout() {
        data[current_slot].Lastlogging = time(nullptr);
        save();
        current_slot = 5;
    }
    bool is_empty_current() {
        return data[current_slot].name.empty();
    }
    void change_name(std::string &name) {
        data[current_slot].name = name;
    }
    void rename(std::string name) {
        data[current_slot].name = name;
        save();
    }
    void remove_save() {
        std::remove((savedatafilePath + "save" + std::to_string(current_slot + 1) + ".sd").data());
        std::remove((savedatafilePath + "save" + std::to_string(current_slot + 1) + ".si").data());
        data[current_slot].name = "";
        current_slot = 0;
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