#pragma once
// 参考元
// https://zenn.dev/reputeless/articles/138607dc091780fecb30
struct BubbleEffect : IEffect
{
	struct Bubble
	{
		Vec2 offset;
		double startTime;
		double scale;
		ColorF color;
	};

	Vec2 m_pos;
	Array<Bubble> m_bubbles;
	float m_lifeTime = 0.5f;

	BubbleEffect(const Vec2& pos, double baseHue);
	bool update(double t) override;
};

