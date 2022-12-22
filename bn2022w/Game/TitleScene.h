#pragma once
#include "WordObject.h"
using App = SceneManager<String>;
class TitleScene : public App::Scene
{
	Array<std::shared_ptr<WordObject>> m_startObjects;
	std::shared_ptr<WordObject> m_selectedWord = nullptr;
	DrawableText m_titleText;
	
public:
	TitleScene(const InitData& init);	// 更新関数（オプション）
	void update() override;
	void draw() const override;
};


