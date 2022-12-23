#pragma once
#include "SharedStruct.h"

class ScoreManager
{
	int m_score = 0;
	int m_scoreBase = 500;
	int m_scoreMin = 10;
	float m_scoreDecay = 5;
	int m_connectCount = 0;
	int m_combo = 0;
	int m_maxCombo = 0;

public:
	int Score() const;
	int Combo() const;
	Result GetResult() const;
	void ResetCombo();
	void ApplyConnect(int connectCount = 1);
	void AddScore(float time);
};

