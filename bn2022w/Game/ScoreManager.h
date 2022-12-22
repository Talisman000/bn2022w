#pragma once
class ScoreManager
{
	int m_score = 0;
	int m_scoreBase = 500;
	int m_scoreMin = 10;
	float m_scoreDecay = 5;
	int m_combo = 0;
	int m_maxCombo = 0;

public:
	int Score() const;
	int Combo() const;
	void ResetCombo();
	void AddCombo(int add = 1);
	void AddScore(float time);
};

