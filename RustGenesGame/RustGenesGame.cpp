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
    if (Users.is_empty()) {
        std::cout << (*language.data.find("save2")).second << '\n' << (*language.data.find("save3")).second << '\n' << (*language.data.find("save4")).second << '\t';
        std::string name;
        std::cin >> name;
        Users.mkprofile(name);
        Users.save();
    }
    else
    {
        std::cout << (*language.data.find("save1")).second << '\n';
    }
    // system("puse");
    return 0;
}