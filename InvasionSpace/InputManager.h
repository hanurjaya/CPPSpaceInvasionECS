#pragma once
#include <SDL3/SDL.h>
#include "GameStateManager.h"
#include "GameObjectManager.h"
#include "Constant.h"
#include "EntityRegistryManager.h"
#include "Position.h"

class InputManager
{
private:
	static InputManager* m_InputManagerInstance;
	const bool* keyboardState = nullptr;
	entt::entity m_playerEntity;
	float m_playerSpeed{ 400.0f };
	Uint64 m_sdlTicks{ SDL_GetTicksNS() };
	InputManager();
	const bool* GetKeyboardState();
public:
	InputManager(InputManager&) = delete;
	void operator=(const InputManager&) = delete;
	static InputManager* GetInstance();
	void Update();
	void SetPlayerEntity(entt::entity playerEntity);
};

