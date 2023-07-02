#include "pch.h"

#define endl '\n'
#define tab '\t'

#include "Utility.h"
#include "Configs.h"
#include "LogsSaver.h"
#include "Language.h"
#include "Saves.h"
#include "Planting_Sites.h"
#include "Game.h"

void if_empty_create(Language &language, Saves &saves) {
	if (saves.is_empty()) {
		std::cout << language["save2"] << endl << language["save3"] << endl << language["save4"] << tab;
		std::string name = getline();
		saves.mkprofile(name);
		saves.save();
	}
}
bool welcome_back(Language& language, Saves& saves) {
	std::cout << language["save1"] << endl;
	if (!saves.qincorrect_names.empty()) {
		saves.print();
		std::cout << language["save10"] << endl;
		while (true) {
			std::cout << saves.qincorrect_names.front() << ":\t";
			std::string input = getline();
			if (input != "0") {
				saves.login(saves.qincorrect_names.front() - 1);
				saves.rename(input);
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

	saves.print();
	std::cout << language["save5"] << endl << language["save6"] + "\t";
	char inputvalue;
	std::cin >> inputvalue;
	int number = atoi(&inputvalue) - 1;
	if (number >= 0 && number <= 4) {
		saves.login(number);
		if (saves.is_empty_current()) {
			std::cout << language["save8"] << endl << language["save9"] << tab;
			std::string name = getline();
			saves.mkprofile(name);
			saves.save();
			return false;
		}
		std::cout << language["save11"] << endl << language["save12"] << endl << language["save13"] << endl << language["save14"] << endl;
		char inputvalue;
		std::cin >> inputvalue;
		if (inputvalue == '1') {
			saves.login(true, 0);
			return true;
		}
		else if (inputvalue == '2') {
			std::cout << language["save9"] << tab;
			std::string name = getline();
			if (name != "0") {
				saves.rename(name);
			}
		}
		else if (inputvalue == '3') {
			std::cout << language["save15"] << tab;
			char confirmation;
			std::cin >> confirmation;
			if (confirmation == '1') {
				saves.remove_save();
			}
		}
	}
	else if (number == -1) {
		return true;
	}
	else
	{
		std::cout << language["save7"] << endl;
		welcome_back(language, saves);
	}

}

int main(int argc, char* argv[])
{
	init();
	Configs configs;
	LogsSaver logsaver(configs);
	Language language(configs);
	consoleCP = language.getCP();
	StartUp(language);
	logsaver.log(1, "message", "Preparation completed successfully");
	Saves saves;
	while (true)
	{
		if_empty_create(language, saves);
		if (welcome_back(language, saves)) {
			break;
		}
	}
	Game game;
	game.start(configs, logsaver, language, saves.getdata());
	

	


	// system("puse");
	return 0;
}