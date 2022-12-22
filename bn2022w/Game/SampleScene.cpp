#include "stdafx.h"
#include "SampleScene.h"

void SampleScene::update()
{
	IScene<String, void>::update();
}

void SampleScene::draw() const
{
	Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });

	FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);

	Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
}
