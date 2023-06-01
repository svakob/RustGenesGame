#include "pch.h"

int randrange(int minimum_number, int max_number) {
	return (rand() % (max_number + 1 - minimum_number)) + minimum_number;
}
int randrange(int max_number) {
	return (rand() % (max_number + 1));
}