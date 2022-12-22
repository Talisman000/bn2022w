#pragma once
#include <map>
class WordObject
{
	std::string m_id;
	bool m_isSelected;
	std::map<std::string, std::string> m_trans = {
		{"ja", "テキスト"},
		{"en", "text"},
		{"ko", "텍스트"},
		{"zh", "文"}
	};
	Circle m_circle;
	DrawableText m_text;
	Vec2 m_position;

public:
	WordObject();
	bool IsSameWord(WordObject& other) const;
	std::string Id();
	bool IsPressed() const;
	bool IsMouseOver() const;
	bool IsReleased() const;
	void Select();
	void update();
	void draw() const;

};

