#include "EnemyMovementManager.h"

EnemyMovementManager* EnemyMovementManager::m_entityMovementManagerInstance = nullptr;

EnemyMovementManager* EnemyMovementManager::GetInstance()
{
	if (m_entityMovementManagerInstance == nullptr)
	{
		m_entityMovementManagerInstance = new EnemyMovementManager();
	}
	return m_entityMovementManagerInstance;
}

void EnemyMovementManager::GetEnemyDirection()
{
	EntityRegistryManager::GetInstance()->GetRegistry()->view<Position, GameplayInfo>().each([&](Position& pos, GameplayInfo& gameplayInfo) {
		if (gameplayInfo.m_scoreWeight > 0)
		{
			if (gameplayInfo.m_isActive)
			{
				if (pos.m_posDetail->x < 30.0f && m_isEnemyMoveLeft)
				{
					m_isEnemyMoveLeft = false;
					m_enemyNeedMoveDown = true;
					return;
				}
				else if (pos.m_posDetail->x + pos.m_posDetail->w > m_width - 30 && !m_isEnemyMoveLeft)
				{
					m_isEnemyMoveLeft = true;
					m_enemyNeedMoveDown = true;
					return;
				}
			}
		}
		});
}

void EnemyMovementManager::Update()
{
	GetEnemyDirection();
	if (GetElapsedTime() >= m_enemySPeed)
	{
		clock_start = SDL_GetTicks();
		clock_now = SDL_GetTicks();

		EntityRegistryManager::GetInstance()->GetRegistry()->view<Position, GameplayInfo>().each([&](Position& pos, GameplayInfo& gameplayInfo) {
			if (gameplayInfo.m_scoreWeight > 0)
			{
				if (gameplayInfo.m_isActive)
				{
					if (m_enemyNeedMoveDown)
					{
						pos.m_posDetail->y += pos.m_posDetail->h;
					}
					else if (m_isEnemyMoveLeft)
					{
						pos.m_posDetail->x -= 10.0f;
					}
					else
					{
						pos.m_posDetail->x += 10.0f;
					}
				}
			}
			});
		if (m_enemyNeedMoveDown)
		{
			m_enemyNeedMoveDown = false;
		}
	}
	else
	{
		clock_now = SDL_GetTicks();
	}
}

EnemyMovementManager::EnemyMovementManager()
{
}

Uint64 EnemyMovementManager::GetElapsedTime()
{
	return clock_now - clock_start;
}

bool EnemyMovementManager::IsNeedToRespawnEnemy()
{
	return EntityRegistryManager::GetInstance()->GetRegistry()->view<Position, GameplayInfo>().size_hint() - 1 <= 0;;
}

void EnemyMovementManager::UpEnemySpeed()
{
	if (m_enemySPeed > 40.0f)
	{
		m_enemySPeed -= 1.0f;
	}
}

void EnemyMovementManager::DownEnemySpeed()
{
	if (m_enemySPeed < 1500.0f)
	{
		m_enemySPeed += 1.0f;
	}
}