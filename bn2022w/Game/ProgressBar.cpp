#include "stdafx.h"
#include "ProgressBar.h"

void ProgressBar::Draw(const Vector2D<int> center, const float width, const float progress) const
{
	const auto startPos = center - Vec2(width / 2, 0);
	auto endPos = center + Vec2(width / 2, 1);
	const auto startIcon = Triangle{startPos, 20, 90_deg};
	const auto endIcon = Rect{Arg::center(endPos.x, endPos.y), 20};
	// leap補完、Vec2じゃないとうまく動かないっぽい…
	const auto startVec2 = Vec2(startPos);
	const auto endVec2 = Vec2(endPos);
	const auto leapPos = startVec2.lerp(endVec2, progress);
	const auto progressIcon = Shape2D::Hexagon(10, leapPos, progress * 360);
	const auto line = Line{startPos, endPos};

	line.draw(LineStyle::RoundDot, 4, Palette::Snow);
	progressIcon.draw(ColorF(Palette::Black, 0)).drawFrame(2, Palette::Snow);
	startIcon.draw(Palette::Snow);
	endIcon.draw(Palette::Snow);

}
