#include "stdafx.h"
#include "GameScene.h"

#include "BubbleEffect.h"
#include "WordReader.h"

GameScene::GameScene(const InitData& init) : IScene{ init }
{
	Scene::SetBackground(ColorF{ 0.1, 0.1, 0.1 });
	m_wordTable = WordReader::Load(U"resources/WordData.bin");
	m_scoreManager.reset(new ScoreManager());
	CreateWordObjects(3);

	m_scoreTextHeader = Font{ 20 }(U"Score");
	m_scoreText = Font{ 28 }(U"0");

	// audio
	m_bgm = Audio{Audio::Stream, Resource(U"resources/wordnnect.ogg")};
	m_bgm.play();
	m_seConnect = Audio{Audio::Stream, Resource(U"resources/se_connect.ogg")};
}

void GameScene::update()
{
	m_elapsedTime += Scene::DeltaTime();
	if (m_elapsedTime > m_timeLimit)
	{
		getData<Result>() = m_scoreManager->GetResult();
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
			m_effect.add<BubbleEffect>(obj->Position(), Random(0.0, 360.0));
			m_effect.add<BubbleEffect>(m_selectedWord->Position(), Random(0.0, 360.0));
			m_seConnect.playOneShot();
			// スコア加算
			m_scoreManager->ApplyConnect();
			m_scoreManager->AddScore(m_selectedWord->ElapsedTime());
			m_scoreText = Font{ 28 }(Format(m_scoreManager->Score()));
#if _DEBUG
			Print << m_scoreManager->Score();
			Print << m_scoreManager->Combo();
#endif
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
	m_effect.update();
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

void GameScene::CreateWordObjects(const int n)
{
	Word word = m_wordTable.begin()->second;
	for (int i = 0; i < n; i++)
	{
		if (IsEven(i))
		{
			auto item = m_wordTable.begin();
			std::advance(item, Random(m_wordTable.size() - 1));
			word = item->second;
		}
		auto obj = std::make_shared<WordObject>(word);
		m_wordObjects << obj;
	}
}
