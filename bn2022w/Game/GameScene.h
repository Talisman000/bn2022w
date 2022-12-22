#pragma once
#include "ProgressBar.h"
#include "ScoreManager.h"
#include "WordObject.h"
using App = SceneManager<String>;
class GameScene : public App::Scene
{
	Array<std::shared_ptr<WordObject>> m_wordObjects;
	std::shared_ptr<WordObject> m_selectedWord = nullptr;
	Effect effect;
	float m_timeLimit = 60;
	float m_elapsedTime = 0;
	int m_clearCount = 0;

	std::shared_ptr<ScoreManager> m_scoreManager = nullptr;
	DrawableText m_scoreTextHeader;
	DrawableText m_scoreText;
	ProgressBar m_progressBar;

public:
	GameScene(const InitData& init);
	void update() override;
	void draw() const override;

	void ClearWordObjects();
	void CreateWordObjects(int n);
};

