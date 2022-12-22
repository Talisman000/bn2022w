#pragma once
#include "flatbuffers/util.h"
#include "WordData_generated.h"

struct Word
{
	String id;
	String ja;
	String en;
	String ko;
	String zh;
};

class WordReader
{
public:
	std::vector<Word> Load();
};

