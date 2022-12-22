#include "stdafx.h"
#include "GameScene.h"

#include "BubbleEffect.h"

GameScene::GameScene(const InitData& init) : IScene{ init }
{
	Scene::SetBackground(ColorF{ 0.1, 0.1, 0.1 });
	m_scoreManager.reset(new ScoreManager());
	for (int i = 0; i < 10; i++)
	{
		auto obj = std::make_shared<WordObject>();
		m_objs << obj;
	}
}

void GameScene::update()
{
	for (auto& obj : m_objs)
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

			Print << m_scoreManager->Score();
			Print << m_scoreManager->Combo();

			// つながった2つのオブジェクトを除外
			m_objs.remove(obj);
			m_objs.remove(m_selectedWord);
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
	if (m_selectedWord != nullptr)
	{
		Line(m_selectedWord->Position(), Cursor::Pos()).draw(Palette::White);
	}
	for (const auto obj : m_objs)
	{
		obj->draw();
	}
}
