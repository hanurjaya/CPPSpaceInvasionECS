#pragma once
class GameplayInfo
{
public:
	float m_scoreWeight = 0.0f;
	bool m_isActive = true;
	bool m_isPlayerShot = false;
	GameplayInfo(float scoreWeight, bool isActive);
};

