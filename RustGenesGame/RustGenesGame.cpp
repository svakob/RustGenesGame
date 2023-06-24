#include "pch.h"
#include "Utility.h"
#include "Configs.h"
#include "LogsSaver.h"
#include "Language.h"
#include "Saves.h"
#include "Planting_Sites.h"

#define endl '\n'
#define tab '\t'

void if_empty_create(Language &language, Saves &saves) {
	if (saves.is_empty()) {
		std::cout << language.data["save2"] << endl << language.data["save3"] << endl << language.data["save4"] << tab;
		std::string name = getline();
		saves.mkprofile(name);
		saves.save();
	}
}
bool welcome_back(Language& language, Saves& saves) {
	std::cout << language.data["save1"] << endl;
	if (!saves.qincorrect_names.empty()) {
		saves.print();
		std::cout << language.data["save10"] << endl;
		while (true) {
			std::cout << saves.qincorrect_names.front() << ":\t";
			std::string input = getline();
			if (input != "0") {
				saves.login(saves.qincorrect_names.front() - 1);
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

	saves.print();
	std::cout << language.data["save5"] << endl << language.data["save6"] + "\t";
	char inputvalue;
	std::cin >> inputvalue;
	int number = atoi(&inputvalue) - 1;
	if (number >= 0 && number <= 4) {
		saves.login(number);
		if (saves.is_empty_current()) {
			std::cout << language.data["save8"] << endl << language.data["save9"] << tab;
			std::string name = getline();
			saves.mkprofile(name);
			saves.save();
			return false;
		}
		std::cout << language.data["save11"] << endl << language.data["save12"] << endl << language.data["save13"] << endl << language.data["save14"] << endl;
		char inputvalue;
		std::cin >> inputvalue;
		if (inputvalue == '1') {
			saves.login(true, 0);
			return true;
		}
		else if (inputvalue == '2') {
			std::cout << language.data["save9"] << tab;
			std::string name = getline();
			if (name != "0") {
				saves.rename(name);
			}
		}
		else if (inputvalue == '3') {
			std::cout << language.data["save15"] << tab;
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
		std::cout << language.data["save7"] << endl;
		welcome_back(language, saves);
	}

}

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

	while (true)
	{
		if_empty_create(language, saves);
		if (welcome_back(language, saves)) {
			break;
		}
	}
	


	// system("puse");
	return 0;
}