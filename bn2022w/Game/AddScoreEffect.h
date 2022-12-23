#pragma once
struct AddScoreEffect : IEffect
{
	Vec2 m_pos;
	DrawableText m_text;
	ColorF m_color;
	float m_lifeTime = 0.5f;

	AddScoreEffect(const Vec2& pos, int score, ColorF color);
	bool update(double t) override;
};

