#pragma once
#include "pch.h"
struct Configs {
	enum Elanguage {
		EN = 0,
		UA = 1
	};
	Elanguage language;
	Configs()
	{
		language = UA;
	}
};