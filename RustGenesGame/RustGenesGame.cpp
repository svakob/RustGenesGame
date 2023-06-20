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
    //StartUp(language);
    logsaver.log(1, "message", "Preparation completed successfully");
    Saves saves;
    if (saves.is_empty()) {
        std::cout << (*language.data.find("save2")).second << endl << (*language.data.find("save3")).second << endl << (*language.data.find("save4")).second << '\t';
        std::string name = getline();
        std::cout << name;
        // saves.mkprofile(name);
        saves.save();
    }
    /*else
    {
        std::cout << (*language.data.find("save1")).second << endl;
        while (true)
        {
            Users.print();
            std::cout << (*language.data.find("save5")).second << endl << (*language.data.find("save6")).second + "\t";
            std::string whattoload;
            std::cin >> whattoload;
            int whatsave = stoi(whattoload);
            if (whatsave >= 1 && whatsave <= 5) {
                save = Users.login(whatsave-1);
                if (save->name == "") {
                    std::cout << (*language.data.find("save8")).second << endl << (*language.data.find("save3")).second << endl << (*language.data.find("save9")).second << "\t";
                    std::string name;
                    std::cin >> name;
                    save->name = name;
                    save->Lastlogging = time(nullptr);
                    save->version = version;
                    Users.save();
                }
                break;
            }
            else
            {
                std::cout << (*language.data.find("save7")).second << endl;
                continue;
            }
        }
    }
    std::cout << (*language.data.find("init2")).second << endl;*/
    // std::this_thread::sleep_for(std::chrono::seconds(1));

    
    // system("puse");
    return 0;
}