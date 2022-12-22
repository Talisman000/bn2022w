#include "stdafx.h"
#include "WordObject.h"

WordObject::WordObject()
{
	// 位置はランダム
	m_position = RandomVec2(Scene::Rect()) * 0.8f;
	m_circle = Circle{ m_position, 30 };
	const auto font = Font{ 20 };
	// ランダムで表示する言語を選択する
	auto item = m_trans.begin();
	std::advance(item, Random(m_trans.size() - 1));
	const auto& key = item->first;
	const auto text = Unicode::Widen(m_trans[key]);
	m_text = font(text);
}

bool WordObject::IsSameWord(std::shared_ptr<WordObject>& other) const
{
	return m_id == other->Id();
}

std::string WordObject::Id()
{
	return m_id;
}
Vec2 WordObject::Position() const
{
	return m_position;
}

float WordObject::ElapsedTime() const
{
	return m_elapsedTime;
}

bool WordObject::IsPressed() const
{
	return m_circle.leftPressed();
}

bool WordObject::IsMouseOver() const
{
	return m_circle.mouseOver();
}

void WordObject::Select()
{
	m_isSelected = true;
}

void WordObject::DeSelect()
{
	m_isSelected = false;
}

void WordObject::update(float delta)
{
	m_elapsedTime += delta;
	m_circle.setPos(m_position);
}

void WordObject::draw() const
{
	auto color = Palette::White;
	if (IsMouseOver()) color = Palette::Yellowgreen;
	if (m_isSelected) color = Palette::Skyblue;
	m_circle.draw(ColorF{ Palette::Snow, 0 }).drawFrame(2, color);
	m_text.drawAt(m_position + Vec2(1, 1), Palette::Darkgray);
	m_text.drawAt(m_position, Palette::Snow);
}
