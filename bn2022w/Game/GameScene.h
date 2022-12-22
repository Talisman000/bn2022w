#pragma once
#include "WordObject.h"
using App = SceneManager<String>;
class GameScene : public App::Scene
{
	Array<WordObject> m_objs;
	WordObject& m_selectedObj;
public:
	GameScene(const InitData& init);
	// 更新関数（オプション）
	void update() override;
	void draw() const override;
};

