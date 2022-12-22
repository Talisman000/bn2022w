#pragma once
using App = SceneManager<String>;
class ResultScene : public App::Scene
{
public:
	ResultScene(const InitData& init) : IScene{ init }
	{

	}
	// 更新関数（オプション）
	void update() override;
	void draw() const override;
};


