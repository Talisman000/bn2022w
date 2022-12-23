#pragma once
#include "WordObject.h"
#include "SharedStruct.h"
using App = SceneManager<String, Result>;
class TitleScene : public App::Scene
{
	Array<std::shared_ptr<WordObject>> m_startObjects;
	std::shared_ptr<WordObject> m_selectedWord = nullptr;
	DrawableText m_titleText;
	DrawableText m_versionText;
	
public:
	TitleScene(const InitData& init);	// 更新関数（オプション）
	void update() override;
	void draw() const override;
};


