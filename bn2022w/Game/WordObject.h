#pragma once
#include <map>
class WordObject
{
	std::string m_id = "id_999_text";
	bool m_isSelected = false;
	float m_elapsedTime = 0;
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
	std::string Id();
	Vec2 Position() const;
	float ElapsedTime() const;
	[[nodiscard]] bool IsSameWord(std::shared_ptr<WordObject>& other) const;
	[[nodiscard]] bool IsPressed() const;
	[[nodiscard]] bool IsMouseOver() const;
	void Select();
	void DeSelect();
	void update(float delta);
	void draw() const;

};

