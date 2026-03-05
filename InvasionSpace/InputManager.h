#pragma once
#include <SDL3/SDL.h>
#include "GameStateManager.h"
#include "Constant.h"
#include "EntityRegistryManager.h"
#include "Position.h"
#include "Sprite.h"
#include "GameplayInfo.h"
#include "EnemyMovementManager.h"
#include "RenderingManager.h"

class InputManager
{
private:
	static InputManager* m_InputManagerInstance;
	const bool* keyboardState = nullptr;
	entt::entity m_playerEntity;
	entt::entity m_projectileEntity;
	float m_projectileSpeed{ 200.0f };
	float m_playerSpeed{ 400.0f };
	Uint64 m_sdlTicks{ SDL_GetTicksNS() };
	InputManager();
	const bool* GetKeyboardState();
	bool TryShotProjectile();
	void ProjectilePosUpdate();
public:
	InputManager(InputManager&) = delete;
	void operator=(const InputManager&) = delete;
	static InputManager* GetInstance();
	void Update();
	void SetPlayerEntity(entt::entity playerEntity);
	void SetProjectileEntity(entt::entity projectileEntity);
};

