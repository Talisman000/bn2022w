#include <iostream>
#include <fstream>

#include "MonsterData_generated.h"

using namespace std;
using namespace Bn2022w::MonsterData;

int main()
{
	ifstream fin("../../MonsterData/MonsterData.bin", ios::in | ios::binary);
	if (!fin)
	{
		return 1;
	}

	auto begin = fin.tellg();
	fin.seekg(0, fin.end);

}
