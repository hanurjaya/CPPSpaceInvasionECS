#pragma once
#include "EntityRegistryManager.h"
#include "Position.h"
#include "GameplayInfo.h"
#include "Constant.h"
#include <SDL3/SDL.h>

class EnemyMovementManager
{
private:
	float m_enemySPeed{ 1000.0f };
	static EnemyMovementManager* m_entityMovementManagerInstance;
	Uint64 clock_start{ SDL_GetTicks() };
	Uint64 clock_now{ SDL_GetTicks() };
	entt::entity m_playerEntity;
	bool m_enemyNeedMoveDown{ false };
	bool m_isEnemyMoveLeft{ true };

	EnemyMovementManager();
	Uint64 GetElapsedTime();
	void GetEnemyDirection();
public:
	EnemyMovementManager(EnemyMovementManager&) = delete;
	void operator=(const EnemyMovementManager&) = delete;
	static EnemyMovementManager* GetInstance();
	void Update();
	bool IsNeedToRespawnEnemy();
	void UpEnemySpeed();
	void DownEnemySpeed();
};

