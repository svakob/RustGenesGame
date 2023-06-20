﻿#pragma once
#include "pch.h"
#include "Language.h"

#define endl '\n'

int randrange(int minimum_number, int max_number) {
    return (rand() % (max_number + 1 - minimum_number)) + minimum_number;
}
int randrange(int max_number) {
    return (rand() % (max_number + 1));
}
std::string getline() {
    SetConsoleCP(1251);
    std::string str;
    std::cin >> str;
    SetConsoleCP(CP_UTF8);
    return str;
}
void init() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::srand(std::time(nullptr));
}
class Timer {
    std::chrono::time_point<std::chrono::steady_clock> start, end;
public:
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }
    auto stop() {
        end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }
};
void StartUp(Language &language) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Alatur soft " << (*language.data.find("init1")).second << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "RustGenesGame" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << (*language.data.find("init2")).second << "\t[";
    for (int i = 0; i < 100; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
        std::cout << u8"■";
    }
    std::cout << "]\n";
}