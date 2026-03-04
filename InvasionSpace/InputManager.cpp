#include "InputManager.h"

InputManager* InputManager::m_InputManagerInstance = nullptr;

InputManager::InputManager()
{

}

InputManager* InputManager::GetInstance()
{
	if (m_InputManagerInstance == nullptr)
	{
		m_InputManagerInstance = new InputManager();
	}
	return m_InputManagerInstance;
}

const bool* InputManager::GetKeyboardState()
{
	return SDL_GetKeyboardState(NULL);
}

void InputManager::Update()
{
	SDL_Event sdl_event;
	SDL_PollEvent(&sdl_event);

	keyboardState = GetKeyboardState();

	if (sdl_event.type == SDL_EVENT_QUIT)
	{
		GameStateManager::GetInstance()->SetGameState(GameStateManager::Exit);
	}

	if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::StartMenu)
	{
		if (keyboardState[SDL_SCANCODE_ESCAPE] || sdl_event.type == SDL_EVENT_QUIT)
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::Exit);
		}
        if (keyboardState[SDL_SCANCODE_RETURN])
        {
            GameStateManager::GetInstance()->SetGameState(GameStateManager::InGame);
        }
	}
	else if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::InGame)
	{
		if (!EntityRegistryManager::GetInstance()->GetRegistry()->any_of<Position>(m_playerEntity))
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameOver);
		}
		if (keyboardState[SDL_SCANCODE_W])
		{
		}
		if (keyboardState[SDL_SCANCODE_A])
		{
			if (EntityRegistryManager::GetInstance()->GetRegistry()->any_of<Position>(m_playerEntity))
			{
				Position* playerPos = &EntityRegistryManager::GetInstance()->GetRegistry()->get<Position>(m_playerEntity);
				if (playerPos->m_posDetail->x > 30.0f)
				{
					playerPos->m_posDetail->x -= m_playerSpeed * ((float)(SDL_GetTicksNS() - m_sdlTicks) / 1000000000.0f);
				}
			}
		}
		if (keyboardState[SDL_SCANCODE_S])
		{
		}
		if (keyboardState[SDL_SCANCODE_D])
		{
			if (EntityRegistryManager::GetInstance()->GetRegistry()->any_of<Position>(m_playerEntity))
			{
				Position* playerPos = &EntityRegistryManager::GetInstance()->GetRegistry()->get<Position>(m_playerEntity);
				if (playerPos->m_posDetail->x + 60 < (m_width - 30))
				{
					playerPos->m_posDetail->x += m_playerSpeed * ((float)(SDL_GetTicksNS() - m_sdlTicks) / 1000000000.0f);
				}
			}
		}
		if (keyboardState[SDL_SCANCODE_SPACE])
		{
			GameObjectManager::GetInstance()->TrySpawnProjectileFromPlayer();
		}
		if (keyboardState[SDL_SCANCODE_F])
		{
			EnemyMovementManager::GetInstance()->UpEnemySpeed();
		}
		if (keyboardState[SDL_SCANCODE_V])
		{
			EnemyMovementManager::GetInstance()->DownEnemySpeed();
		}
	}
	else if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::GameOver)
	{
		if (keyboardState[SDL_SCANCODE_Y])
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::InGame);
		}
		if (keyboardState[SDL_SCANCODE_N])
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::Exit);
		}
	}
	m_sdlTicks = SDL_GetTicksNS();
}

void InputManager::SetPlayerEntity(entt::entity playerEntity)
{
	m_playerEntity = playerEntity;
}
