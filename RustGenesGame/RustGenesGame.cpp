#include "pch.h"
#include "Utility.h"
#include "Configs.h"
#include "LogsSaver.h"
#include "Language.h"
#include "Profile.h"
#include "Planting_Sites.h"

int main(int argc, char* argv[])
{
    init();
    Configs configs;
    LogsSaver logsaver(configs);
    Language language(configs);
    //StartUp(language);
    logsaver.log(1, "message", "Preparation completed successfully");
    Saves Users;
    UserData* save;
    if (Users.is_empty()) {
        std::cout << (*language.data.find("save2")).second << '\n' << (*language.data.find("save3")).second << '\n' << (*language.data.find("save4")).second << '\t';
        std::string name;
        std::cin >> name;
        Users.mkprofile(name);
        Users.save();
        save = Users.login(0);
    }
    else
    {
        std::cout << (*language.data.find("save1")).second << '\n';
        while (true)
        {
            Users.print();
            std::cout << (*language.data.find("save5")).second << "\n" << (*language.data.find("save6")).second + "\t";
            std::string whattoload;
            std::cin >> whattoload;
            if (std::stoi(whattoload) >= 1 && std::stoi(whattoload) <= 5) {
                save = Users.login(std::stoi(whattoload)-1);
                if (save->name == "") {
                    std::cout << (*language.data.find("save8")).second << "\n" << (*language.data.find("save3")).second << "\n" << (*language.data.find("save9")).second << "\t";
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
                std::cout << (*language.data.find("save7")).second << "\n";
                continue;
            }
        }
    }
    std::cout << (*language.data.find("init2")).second;
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // system("puse");
    return 0;
}