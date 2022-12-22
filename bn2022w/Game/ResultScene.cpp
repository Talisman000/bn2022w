#include "stdafx.h"
#include "ResultScene.h"

ResultScene::ResultScene(const InitData& init) : IScene{ init }
{
	Scene::SetBackground(ColorF{ 0.1, 0.1, 0.1 });
	m_resultText = Font{ 100, Typeface::Light }(U"Result");
	m_gotoTitleText = Font{ 24, Typeface::Light }(U"Left Click -------- Title");
}

void ResultScene::update()
{
	m_elapsedTime += Scene::DeltaTime();
	if (m_elapsedTime < m_gotoTitleWaitTime)return;
	if (MouseL.down())
	{
		changeScene(U"TitleScene");
	}
}

void ResultScene::draw() const
{
	m_resultText.drawAt(400, 100);
	if (m_elapsedTime < m_gotoTitleWaitTime)return;
	m_gotoTitleText.drawAt(400, 500);
}
