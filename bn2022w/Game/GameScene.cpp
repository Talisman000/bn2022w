#include "stdafx.h"
#include "GameScene.h"

#include "BubbleEffect.h"
#include "WordReader.h"

GameScene::GameScene(const InitData& init) : IScene{init}
{
	WordReader wordReader;
	auto list = wordReader.Load();
	for (auto& word: list)
	{
		m_wordList.push_back(word);
		
	}
	Scene::SetBackground(ColorF{0.1, 0.1, 0.1});
	m_scoreManager.reset(new ScoreManager());
	CreateWordObjects(3);

	m_scoreTextHeader = Font{20}(U"Score");
	m_scoreText = Font{28}(U"0");
}

void GameScene::update()
{
	m_elapsedTime += Scene::DeltaTime();
	if (m_elapsedTime > m_timeLimit)
	{
		changeScene(U"ResultScene");
	}
	if (m_wordObjects.size() < 2)
	{
		ClearWordObjects();
		const auto numObject = m_clearCount / 5 + 3;
		CreateWordObjects(numObject);
		return;
	}
	for (auto& obj : m_wordObjects)
	{
		obj->update(Scene::DeltaTime());
		if (m_selectedWord != nullptr)
		{
			// 別のオブジェクト同士が同じ単語を指している場合の処理
			if (!MouseL.up()) continue;
			if (!obj->IsMouseOver()) continue;
			if (obj == m_selectedWord) continue;
			if (!m_selectedWord->IsSameWord(obj)) continue;
			// エフェクト出現
			effect.add<BubbleEffect>(obj->Position(), Random(0.0, 360.0));
			effect.add<BubbleEffect>(m_selectedWord->Position(), Random(0.0, 360.0));
			// スコア加算
			m_scoreManager->AddScore(m_selectedWord->ElapsedTime());
			m_scoreManager->AddCombo();
			m_scoreText = Font{28}(Format(m_scoreManager->Score()));

			Print << m_scoreManager->Score();
			Print << m_scoreManager->Combo();

			// つながった2つのオブジェクトを除外
			m_wordObjects.remove(obj);
			m_wordObjects.remove(m_selectedWord);
			m_selectedWord->DeSelect();
			m_selectedWord = nullptr;
			break;
		}
		if (obj->IsPressed())
		{
			// オブジェクト選択
			m_selectedWord = obj;
			m_selectedWord->Select();
			Print << Unicode::Widen(m_selectedWord->Id());
		}
	}
	if (m_selectedWord != nullptr)
	{
		if (MouseL.up())
		{
			m_selectedWord->DeSelect();
			m_selectedWord = nullptr;
		}
	}
	effect.update();
}

void GameScene::draw() const
{
	auto const sceneRect = Scene::Rect();
	//UI関連描画
	auto const x = sceneRect.rightX() / 2;
	m_scoreTextHeader.drawAt(x, 20, Palette::Snow);
	m_scoreText.drawAt(x, 48, Palette::Snow);

	m_progressBar.Draw(Vector2D(sceneRect.rightX() / 2, sceneRect.topY() + 80), sceneRect.w - 50,
	                   m_elapsedTime / m_timeLimit);

	if (m_selectedWord != nullptr)
	{
		Line(m_selectedWord->Position(), Cursor::Pos()).draw(Palette::White);
	}
	for (const auto obj : m_wordObjects)
	{
		obj->draw();
	}
}

void GameScene::ClearWordObjects()
{
	m_wordObjects.clear();
	m_clearCount++;
}

void GameScene::CreateWordObjects(int n)
{
	Word word = m_wordList[0];
	for (int i = 0; i < n; i++)
	{
		if (IsEven(i))
		{
			const auto random = Random(m_wordList.size() - 1);
			word = m_wordList[random];
		}
		auto obj = std::make_shared<WordObject>(word);
		m_wordObjects << obj;
	}
}
