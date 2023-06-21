#include "pch.h"
#include "Utility.h"
#include "Configs.h"
#include "LogsSaver.h"
#include "Language.h"
#include "Saves.h"
#include "Planting_Sites.h"

#define endl '\n'

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
        std::cout << (*language.data.find("save2")).second << endl << (*language.data.find("save3")).second << endl << (*language.data.find("save4")).second << '\t';
        std::string name = getline();
        saves.mkprofile(name);
        saves.save();
    }
    else
    {
        std::cout << (*language.data.find("save1")).second << endl;
        while (true)
        {
            saves.print();
            std::cout << (*language.data.find("save5")).second << endl << (*language.data.find("save6")).second + "\t";
            char whattoload;
            std::cin >> whattoload;
            int whatsave = atoi(&whattoload);
            if (whatsave >= 1 && whatsave <= 5) {

                break;
            }
            else
            {
                std::cout << (*language.data.find("save7")).second << endl;
                continue;
            }
        }
    }
    std::cout << (*language.data.find("init2")).second << endl;
    // std::this_thread::sleep_for(std::chrono::seconds(1));

    
    // system("puse");
    return 0;
}