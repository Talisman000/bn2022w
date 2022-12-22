#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(const InitData& init) : IScene{ init }
{
	Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });
	for (int i = 0; i < 10; i++)
	{
		auto obj = WordObject();
		m_objs << obj;
	}
}

void GameScene::update()
{
	for(auto obj: m_objs)
	{
		obj.update();
	}
}

void GameScene::draw() const
{
	for(auto obj : m_objs)
	{
		obj.draw();
	}
}
