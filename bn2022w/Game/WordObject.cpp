#include "stdafx.h"
#include "WordObject.h"

WordObject::WordObject()
{
	m_id = Random(5); // debug
	m_position = RandomVec2(Scene::Rect());
	m_circle = Circle{ m_position, 20 };
	const auto font = Font{ 20 };
	auto item = m_trans.begin();
	std::advance(item, Random(m_trans.size() - 1));
	const auto& key = item->first;
	const auto text = Unicode::Widen(m_trans[key]);
	m_text = font(text);
}

bool WordObject::IsSameWord(WordObject& other) const
{
	return m_id == other.Id();
}

std::string WordObject::Id()
{
	return m_id;
}

bool WordObject::IsPressed() const
{
	return m_circle.leftPressed();
}

bool WordObject::IsMouseOver() const
{
	return m_circle.mouseOver();
}

bool WordObject::IsReleased() const
{
	return m_circle.leftReleased();
}

void WordObject::update()
{
	m_circle.setPos(m_position);
}

void WordObject::draw() const
{
	m_circle.draw(m_isSelected ? Palette::Skyblue : Palette::White);
	m_text.drawAt(m_position, Palette::Black);
}
