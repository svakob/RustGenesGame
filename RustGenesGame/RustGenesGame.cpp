#include "pch.h"
#include "Utility.h"
#include "Configs.h"
#include "LogsSaver.h"
#include "Planting_Sites.h"

int main()
{
    init();
    // StartUp();
    Configs configs;
    LogsSaver logsaver(configs);
    logsaver.log(1, "message", "Preparation completed successfully");
    return 0;
}