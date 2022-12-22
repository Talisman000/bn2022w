#pragma once
using App = SceneManager<String>;
class SampleScene : public App::Scene
{
public:
	SampleScene(const InitData& init) : IScene{ init }
	{

	}
	// 更新関数（オプション）
	void update() override;
	void draw() const override;
};

