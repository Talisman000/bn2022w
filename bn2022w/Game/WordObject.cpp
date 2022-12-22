#include "stdafx.h"
#include "WordObject.h"

WordObject::WordObject()
{
	const auto sceneRect = Scene::Rect();
	constexpr int offset = 100;

	const auto rectFixed = RectF(offset, offset + 40, sceneRect.w - offset*2, sceneRect.h - offset*2);

	// 位置はランダム
	m_positionTarget = RandomVec2(rectFixed);

	// 最初の出現位置は画面外
	const int height = sceneRect.h;
	const int width = sceneRect.w;
	Array<Vec2> initPos = {
		Vec2(-offset, height / 2),
		Vec2(width / 2, -offset),
		Vec2(width + offset, height / 2),
		Vec2(width / 2, height + offset)
	};
	m_positionInit = initPos[Random(initPos.size() - 1)];

	m_position = m_positionInit;

	m_circle = Circle{m_position, m_shapeSize};
	m_shape = Shape2D::Pentagon(m_shapeSize, m_position, Random(180));
	const auto font = Font{20, Typeface::CJK_Regular_JP};
	// addFallbackすると謎のアクセスエラーが出る
	// const auto fontJP = Font{ 20, Typeface::CJK_Regular_JP };
	// font.addFallback(fontJP);
	// ランダムで表示する言語を選択する
	auto item = m_trans.begin();
	std::advance(item, Random(m_trans.size() - 1));
	const auto& key = item->first;
	const auto text = m_trans[key];
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

	const double e = EaseOutQuart(Min(m_elapsedTime, 1.0f));

	m_position = m_positionInit.lerp(m_positionTarget, e);

	m_shape = Shape2D::Pentagon(m_shapeSize, m_position, m_elapsedTime * 5);
	m_circle.setPos(m_position);
}

void WordObject::draw() const
{
	auto color = Palette::White;
	if (IsMouseOver()) color = Palette::Yellowgreen;
	if (m_isSelected) color = Palette::Skyblue;
	// m_circle.draw(ColorF{ Palette::Snow, 0 }).drawFrame(2, color);
	m_shape.draw(ColorF{Palette::Black, 0}).drawFrame(2, color);
	m_text.drawAt(m_position + Vec2(1, 1), Palette::Darkgray);
	m_text.drawAt(m_position, Palette::Snow);
}
