#pragma once
using App = SceneManager<String>;
class ResultScene : public App::Scene
{
	DrawableText m_resultText;
	DrawableText m_gotoTitleText;
	float m_elapsedTime = 0;
	float m_gotoTitleWaitTime = 3;
public:
	ResultScene(const InitData& init);
	// 更新関数（オプション）
	void update() override;
	void draw() const override;
};


