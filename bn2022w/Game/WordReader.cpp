#include "stdafx.h"
#include "WordReader.h"

std::vector<Word> WordReader::Load()
{
	std::vector<uint8_t> dataBuffer;
	std::vector<Word> WordList;
	BinaryReader reader(U"../Resources/WordData.bin");
	if (reader)
	{
		Print << U"a";
		dataBuffer.resize(reader.size());
		reader.read(dataBuffer.data(), reader.size());

		auto words = Bn2022w::WordData::GetWordList(dataBuffer.data());
		for (const auto& it : *words->word_list())
		{
			Word word;
			word.id = it->id()->c_str();
			word.ja = it->ja()->c_str();
			word.en = it->en()->c_str();
			word.ko = it->ko()->c_str();
			word.zh = it->zh()->c_str();
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
		String a = Unicode::FromUTF8(word.id);
		Print << a << Unicode::FromUTF8(word.ko);
	}
#endif
	return WordList;
}
