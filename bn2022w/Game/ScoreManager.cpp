#include "stdafx.h"
#include "ScoreManager.h"

int ScoreManager::Score() const
{
	return m_score;
}

int ScoreManager::Combo() const
{
	return m_combo;
}

void ScoreManager::ResetCombo()
{
	if (m_maxCombo < m_combo)
	{
		m_maxCombo = m_combo;
	}
	m_combo = 0;
}

void ScoreManager::AddCombo(const int add)
{
	m_combo += add;
}

//スコアは基本スコアからの減点方式（出現からの時間がたてば立つほどスコアが小さくなる）
void ScoreManager::AddScore(const float time)
{
	const auto magnification = (m_scoreDecay - time) / m_scoreDecay;
	auto add = static_cast<int>(static_cast<float>(m_scoreBase) * magnification * (1 + static_cast<float>(m_combo) * 0.1f));
	if (add < m_scoreMin) add = m_scoreMin;
	m_score += add;
}
