#include "stdafx.h"
#include "WordReader.h"


std::vector<Word> WordReader::Load()
{
	std::vector<uint8_t> dataBuffer;
	std::vector<Word> WordList;
	BinaryReader reader(U"../Resources/WordData.bin");
	if (reader)
	{
		dataBuffer.resize(reader.size());
		reader.read(dataBuffer.data(), reader.size());

		auto words = Bn2022w::WordData::GetWordList(dataBuffer.data());
		for (const auto& it : *words->word_list())
		{
			Word word(
				Unicode::FromUTF8(it->id()->c_str()),
				Unicode::FromUTF8(it->ja()->c_str()),
				Unicode::FromUTF8(it->en()->c_str()),
				Unicode::FromUTF8(it->ko()->c_str()),
				Unicode::FromUTF8(it->zh()->c_str())
			);
			WordList.push_back(word);
		}
	}
	else
	{
		throw Error{U"Failed to open binary file"};
	}

#if _DEBUG
	for (const auto& word: WordList)
	{
		Print << word.id;
	}
#endif
	return WordList;
}
