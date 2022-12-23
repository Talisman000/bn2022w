#pragma once
#include "SharedStruct.h"
using App = SceneManager<String, Result>;
class ResultScene : public App::Scene
{
	DrawableText m_resultHeaderText;
	DrawableText m_gotoTitleText;
	DrawableText m_resultTextHeader;
	DrawableText m_resultText;
	float m_elapsedTime = 0;
	float m_gotoTitleWaitTime = 3;
public:
	ResultScene(const InitData& init);
	// 更新関数（オプション）
	void update() override;
	void draw() const override;
};


