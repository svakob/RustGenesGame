#include "pch.h"
#include "Utility.h"
#include "Configs.h"
#include "LogsSaver.h"
#include "Language.h"
#include "Saves.h"
#include "Planting_Sites.h"

#define endl '\n'
#define tab '\t'

int main(int argc, char* argv[])
{
    init();
    Configs configs;
    LogsSaver logsaver(configs);
    Language language(configs);
    consoleCP = language.consoleCP;
    // StartUp(language);
    logsaver.log(1, "message", "Preparation completed successfully");
    Saves saves;
    
    if (saves.is_empty()) {
        std::cout << language.data["save2"] << endl << language.data["save3"] << endl << language.data["save4"] << tab;
        std::string name = getline();
        saves.mkprofile(name);
        saves.save();
    }
    else
    {
        std::cout << language.data["save1"] << endl;
        if (!saves.qincorrect_names.empty()) {
            saves.print();
            std::cout << language.data["save10"] << endl;
            while (true) {
                std::cout << saves.qincorrect_names.front() << ":\t";
                std::string input = getline();
                if (input != "0") {
                    saves.login(saves.qincorrect_names.front()-1);
                    saves.change_name(input);
                    saves.qincorrect_names.pop();
                }
                else
                {
                    saves.qincorrect_names.pop();
                }
                if (saves.qincorrect_names.empty()) {
                    break;
                }
            }
        }
        while (true)
        {
            saves.print();
            std::cout << language.data["save5"] << endl << language.data["save6"] + "\t";
            char inputvalue;
            std::cin >> inputvalue;
            int number = atoi(&inputvalue)-1;
            if (number >= 0 && number <= 4) {
                saves.login(number);
                if (saves.is_empty_current()) {
                    std::cout << language.data["save8"] << endl << language.data["save9"] << tab;
                    std::string name = getline();
                    saves.mkprofile(name);
                    saves.save();
                }
                break;
            }
            else
            {
                std::cout << language.data["save7"] << endl;
                continue;
            }
        }
    }
    std::cout << language.data["init2"] << endl;

    // std::this_thread::sleep_for(std::chrono::seconds(1));

    
    // system("puse");
    return 0;
}