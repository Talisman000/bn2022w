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

Result ScoreManager::GetResult() const
{
	const Result result(m_score, m_connectCount, m_maxCombo);
	return result;
}

void ScoreManager::ResetCombo()
{
	m_combo = 0;
}

void ScoreManager::ApplyConnect(int connectCount)
{
	m_connectCount += connectCount;
	m_combo += connectCount;
	if (m_maxCombo < m_combo)
	{
		m_maxCombo = m_combo;
	}
}

//スコアは基本スコアからの減点方式（出現からの時間がたてば立つほどスコアが小さくなる）
void ScoreManager::AddScore(const float time)
{
	const auto magnification = (m_scoreDecay - time) / m_scoreDecay;
	auto add = static_cast<int>(static_cast<float>(m_scoreBase) * magnification * (1 + static_cast<float>(m_combo) * 0.1f));
	if (add < m_scoreMin) add = m_scoreMin;
	m_score += add;
}
