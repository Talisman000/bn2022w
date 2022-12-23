#include "stdafx.h"
#include "TitleScene.h"

const String kVersion = U"ver.0.2.0";
TitleScene::TitleScene(const InitData& init) :IScene{ init }
{
	Scene::SetBackground(ColorF{ 0.1, 0.1, 0.1 });
	m_titleText = Font{ 100, Typeface::Light }(U"Wordnnect");
	m_versionText = Font{ 18, Typeface::Light }(kVersion);
	auto systemWordTable = WordReader::Load(U"resources/SystemData.bin");
	auto startWord = systemWordTable[U"system_0_connect"];
	auto start_left = WordObject(startWord, "ja");
	auto start_rignt = WordObject(startWord);
	auto sceneRect = Scene::Rect();
	start_left.SetPositionTarget(Vec2(sceneRect.w * 0.3, sceneRect.h * 0.8));
	start_rignt.SetPositionTarget(Vec2(sceneRect.w * 0.7, sceneRect.h * 0.8));
	m_startObjects << std::make_shared<WordObject>(start_left);
	m_startObjects << std::make_shared<WordObject>(start_rignt);
}

void TitleScene::update()
{
	if (m_startObjects.size() == 0)
	{
		changeScene(U"GameScene");
	}
	// GameSceneと同様の処理を書いてるため、共通化したい
	for (auto& obj : m_startObjects)
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
			// つながった2つのオブジェクトを除外
			m_startObjects.remove(obj);
			m_startObjects.remove(m_selectedWord);
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
}

void TitleScene::draw() const
{
	m_titleText.drawAt(400, 200);
	m_versionText.drawAt(44, 585);
	if (m_selectedWord != nullptr)
	{
		Line(m_selectedWord->Position(), Cursor::Pos()).draw(Palette::White);
	}
	for (auto& obj : m_startObjects)
	{
		obj->draw();
	}
}
