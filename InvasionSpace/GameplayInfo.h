#pragma once
class GameplayInfo
{
public:
	float m_scoreWeight = 0.0f;
	bool m_isActive = true;
	GameplayInfo(float scoreWeight, bool isActive);
};

