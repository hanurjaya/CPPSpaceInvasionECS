#include "CollisionManager.h"

CollisionManager* CollisionManager::m_collisionManagerInstance = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager* CollisionManager::GetInstance()
{
	if (m_collisionManagerInstance == nullptr)
	{
		m_collisionManagerInstance = new CollisionManager();
	}
	return m_collisionManagerInstance;
}

bool CollisionManager::CheckCollision(const SDL_FRect* a, const SDL_FRect* b)
{
	//The sides of the rectangles
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a->x;
	rightA = a->x + a->w;
	topA = a->y;
	bottomA = a->y + a->h;

	//Calculate the sides of rect B
	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void CollisionManager::DestroyInactiveObject()
{
	//EntityRegistryManager::GetInstance()->GetRegistry()->
}

void CollisionManager::SetPlayerEntity(entt::entity playerEntity)
{
	m_playerEntity = playerEntity;
}

void CollisionManager::Update()
{
	GameplayInfo& playerInfo = EntityRegistryManager::GetInstance()->GetRegistry()->get<GameplayInfo>(m_playerEntity);
	Position& playerPos = EntityRegistryManager::GetInstance()->GetRegistry()->get<Position>(m_playerEntity);

	//code to check collision
	EntityRegistryManager::GetInstance()->GetRegistry()->view<Position, GameplayInfo>().each([&](auto entity, Position& pos, GameplayInfo& gameplayInfo) {
		if (entity != m_playerEntity)
		{
			if (playerInfo.m_isActive && gameplayInfo.m_isActive && CheckCollision(playerPos.m_posDetail, pos.m_posDetail))
			{
				playerInfo.m_isActive = false;
			}
		}
		});

	for (auto [entity, gameplayInfo] : EntityRegistryManager::GetInstance()->GetRegistry()->view<GameplayInfo>().each())
	{
		if (!gameplayInfo.m_isActive)
		{
			EntityRegistryManager::GetInstance()->GetRegistry()->remove<Sprite, Position, GameplayInfo>(entity);
		}
	}
}
