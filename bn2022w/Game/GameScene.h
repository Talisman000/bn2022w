#pragma once

#include "WordReader.h"
#include "ProgressBar.h"
#include "ScoreManager.h"
#include "WordObject.h"
#include "SharedStruct.h"
using App = SceneManager<String, Result>;

class GameScene : public App::Scene
{
	HashTable<String, Word> m_wordTable;
	Array<std::shared_ptr<WordObject>> m_wordObjects;
	std::shared_ptr<WordObject> m_selectedWord = nullptr;
	Effect m_effect;
	float m_timeLimit = 64;
	float m_elapsedTime = 0;
	int m_clearCount = 0;

	std::shared_ptr<ScoreManager> m_scoreManager = nullptr;
	DrawableText m_scoreTextHeader;
	DrawableText m_scoreText;
	ProgressBar m_progressBar;

	Audio m_bgm;
	Audio m_seConnect;

public:
	GameScene(const InitData& init);
	void update() override;
	void draw() const override;

	void ClearWordObjects();
	void CreateWordObjects(int n);
};
