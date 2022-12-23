#include "stdafx.h"
#include "ResultScene.h"

ResultScene::ResultScene(const InitData& init) : IScene{ init }
{
	Scene::SetBackground(ColorF{ 0.1, 0.1, 0.1 });
	m_resultHeaderText = Font{ 100, Typeface::Light }(U"Result");
	m_gotoTitleText = Font{ 24, Typeface::Light }(U"Left Click --> Title");
	const auto& result = getData<Result>();
	m_resultTextHeader = Font{ 24, Typeface::Light }(U"Score\nConnect");
	m_resultText = Font{ 24, Typeface::Light }(U"{}\n{}"_fmt(result.m_score, result.m_connectCount));
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
	m_resultHeaderText.drawAt(400, 100);
	m_resultTextHeader.drawAt(300, 300);
	m_resultText.drawAt(500, 300);
	if (m_elapsedTime < m_gotoTitleWaitTime)return;
	m_gotoTitleText.drawAt(400, 500);
}
