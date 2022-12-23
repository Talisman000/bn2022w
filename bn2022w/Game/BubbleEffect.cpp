#include "stdafx.h"
#include "BubbleEffect.h"

BubbleEffect::BubbleEffect(const Vec2& pos, double baseHue) : m_pos{ pos }
{
	for (int32 i = 0; i < 8; ++i)
	{
		Bubble bubble{
			.offset = RandomVec2(Circle{30}),
			.startTime = Random(-0.3, 0.1), // 登場の時間差
			.scale = Random(0.1, 1.2),
			.color = HSV{ baseHue + Random(-30.0, 30.0) }
		};
		m_bubbles << bubble;
	}
}

bool BubbleEffect::update(double t)
{
	for (const auto& bubble : m_bubbles)
	{
		const double t2 = (bubble.startTime + t);

		if (not InRange(t2, 0.0, 1.0))
		{
			continue;
		}

		const double e = EaseOutExpo(t2);

		Circle{ (m_pos + bubble.offset + (bubble.offset * 4 * t)), (e * 40 * bubble.scale) }
			.draw(ColorF{ bubble.color, 0.15 * (m_lifeTime - t) / m_lifeTime })
			.drawFrame((30.0 * (1.0 - e) * bubble.scale), ColorF(bubble.color, 1 * (m_lifeTime - t) / m_lifeTime));
	}

	return (t < m_lifeTime);
}
