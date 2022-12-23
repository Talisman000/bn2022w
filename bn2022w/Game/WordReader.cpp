#include "stdafx.h"
#include "WordReader.h"


// idをキーとしたWordクラスのハッシュテーブルとして読み込む
HashTable<String, Word> WordReader::Load()
{
	HashTable<String, Word> table;
	std::vector<uint8_t> dataBuffer;
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
			table.emplace(word.id, word);
		}
	}
	else
	{
		throw Error{U"Failed to open binary file"};
	}

#if _DEBUG
	for (const auto& word: table)
	{
		Print << word.second.id;
	}
#endif
	return table;
}
