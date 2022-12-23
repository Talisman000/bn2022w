#include "stdafx.h"
#include "AddScoreEffect.h"

AddScoreEffect::AddScoreEffect(const Vec2& pos, int score, ColorF color) : m_pos{ pos }, m_color{ color }
{
	m_text = Font{ 24 }(U"+{}"_fmt(score));
}

bool AddScoreEffect::update(double t)
{
	const auto eOutExpo = EaseOutExpo(t / m_lifeTime);
	const auto eInExpo = EaseInExpo(t / m_lifeTime);
	m_text.drawAt(m_pos + Vec2(0, -10.0 * eOutExpo), ColorF{ m_color, 1 - eInExpo });
	return (t < m_lifeTime);
}
