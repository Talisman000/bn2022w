#pragma once
#include "ScoreManager.h"
#include "WordObject.h"
using App = SceneManager<String>;
class GameScene : public App::Scene
{
	Array<std::shared_ptr<WordObject>> m_objs;
	std::shared_ptr<WordObject> m_selectedWord = nullptr;
	std::shared_ptr<ScoreManager> m_scoreManager = nullptr;
	Effect effect;
public:
	GameScene(const InitData& init);
	// 更新関数（オプション）
	void update() override;
	void draw() const override;
};

