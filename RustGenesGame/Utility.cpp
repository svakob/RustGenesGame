#include "pch.h"
#include "Utility.h"

int randrange(int minimum_number, int max_number) {
	return (rand() % (max_number + 1 - minimum_number)) + minimum_number;
}
int randrange(int max_number) {
	return (rand() % (max_number + 1));
}
void Preparation() {
	SetConsoleOutputCP(CP_UTF8);
	std::srand(std::time(NULL));
}