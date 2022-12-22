#pragma once
#include "flatbuffers/util.h"
#include "WordData_generated.h"

struct Word
{
	const char* id;
	const char* ja;
	const char* en;
	const char* ko;
	const char* zh;
};

class WordReader
{
public:
	std::vector<Word> Load();
};

