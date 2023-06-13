#include "pch.h"
#include "Utility.h"
#include "Configs.h"
#include "LogsSaver.h"
#include "Language.h"
#include "Planting_Sites.h"

int main()
{
    init();
    Configs configs;
    LogsSaver logsaver(configs);
    Language language(configs);
    StartUp(language);
    logsaver.log(1, "message", "Preparation completed successfully");
    return 0;
}