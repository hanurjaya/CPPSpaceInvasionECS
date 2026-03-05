#pragma once
#include "EntityRegistryManager.h"
#include "Position.h"
#include "GameplayInfo.h"
#include "Sprite.h"
#include <SDL3/SDL.h>
class CollisionManager
{
private:
	static CollisionManager* m_collisionManagerInstance;
	entt::entity m_playerEntity;
	entt::entity m_projectileEntity;
	int m_totalScore{ 0 };
	CollisionManager();
	bool CheckCollision(const SDL_FRect* a, const SDL_FRect* b);
	void DestroyInactiveObject();
public:
	CollisionManager(CollisionManager&) = delete;
	void operator=(const CollisionManager&) = delete;
	static CollisionManager* GetInstance();
	void Update();
	void SetPlayerEntity(entt::entity playerEntity);
	void SetProjectileEntity(entt::entity m_projectileEntity);
	int GetTotalScore();
};

