#pragma once
#include <map>
#include "WordReader.h"

class WordObject
{
	String m_id = U"debug_text";
	HashTable<std::string, String> m_trans = {
		{"ja", U"テキスト"},
		{"en", U"text"},
		{"ko", U"텍스트"},
		{"zh", U"课本"}
	};


	// 更新情報
	// 現在選択されているか？
	bool m_isSelected = false;
	// オブジェクトが生成されてからの経過時間
	float m_elapsedTime = 0;
	// オブジェクトの現在位置
	Vec2 m_position;
	// オブジェクトが到達する目標の位置（画面外に出現して短い時間をかけてこの座標まで到達する）
	Vec2 m_positionTarget;
	// オブジェクトの初期位置（線形補間をするために使用）
	Vec2 m_positionInit;


	// 描画関連
	float m_shapeSize = 40;
	// 当たり判定として使用
	Circle m_circle;
	// 描画用　ぐるぐる回転させる
	Shape2D m_shape;
	DrawableText m_text;


public:
	WordObject(std::string key = "");
	WordObject(const Word& word, std::string key = "");
	void Init(std::string key);
	String Id();
	Vec2 Position() const;
	float ElapsedTime() const;
	[[nodiscard]] bool IsSameWord(std::shared_ptr<WordObject>& other) const;
	[[nodiscard]] bool IsPressed() const;
	[[nodiscard]] bool IsMouseOver() const;
	void Select();
	void DeSelect();
	void SetPositionTarget(Vec2 pos);
	void update(float delta);
	void draw() const;
};
