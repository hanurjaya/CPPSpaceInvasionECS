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

bool InputManager::TryShotProjectile()
{
	auto playerInfo = EntityRegistryManager::GetInstance()->GetRegistry()->get<GameplayInfo, Position>(m_playerEntity);
	if (!EntityRegistryManager::GetInstance()->GetRegistry()->orphan(m_playerEntity) && !playerInfo._Myfirst._Val.m_isPlayerShot)
	{
		float x = playerInfo._Get_rest()._Myfirst._Val.m_posDetail->x + (playerInfo._Get_rest()._Myfirst._Val.m_posDetail->w / 2) - ((8 / 2) / 2);
		float y = playerInfo._Get_rest()._Myfirst._Val.m_posDetail->y - (30 / 2);

		EntityRegistryManager::GetInstance()->GetRegistry()->emplace<Sprite>(m_projectileEntity, RenderingManager::GetInstance()->LoadTexture("projectile.png"), new SDL_FRect{ 0, 0, 8, 30 });
		EntityRegistryManager::GetInstance()->GetRegistry()->emplace<Position>(m_projectileEntity, new SDL_FRect{ x, y, 8 / 2, 30 / 2 });
		EntityRegistryManager::GetInstance()->GetRegistry()->emplace<GameplayInfo>(m_projectileEntity, 0, true);

		playerInfo._Myfirst._Val.m_isPlayerShot = true;
		return true;
	}
	return false;
}

void InputManager::ProjectilePosUpdate()
{
	if (!EntityRegistryManager::GetInstance()->GetRegistry()->orphan(m_projectileEntity) 
		&& !EntityRegistryManager::GetInstance()->GetRegistry()->orphan(m_playerEntity))
	{
		auto projectileInfo = EntityRegistryManager::GetInstance()->GetRegistry()->get<GameplayInfo, Position>(m_projectileEntity);
		if (projectileInfo._Get_rest()._Myfirst._Val.m_posDetail->y < 32)
		{
			projectileInfo._Myfirst._Val.m_isActive = false;
			EntityRegistryManager::GetInstance()->GetRegistry()->get<GameplayInfo>(m_playerEntity).m_isPlayerShot = false;
		}
		else
		{
			projectileInfo._Get_rest()._Myfirst._Val.m_posDetail->y -= m_projectileSpeed * ((float)(SDL_GetTicksNS() - m_sdlTicks) / 1000000000.0f);
		}
	}
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
		if (EntityRegistryManager::GetInstance()->GetRegistry()->orphan(m_playerEntity))
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
			TryShotProjectile();
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
			EntityRegistryManager::GetInstance()->GetRegistry()->clear<Sprite, Position, GameplayInfo>();
		}
		if (keyboardState[SDL_SCANCODE_N])
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::Exit);
		}
	}
	ProjectilePosUpdate();
	m_sdlTicks = SDL_GetTicksNS();
}

void InputManager::SetPlayerEntity(entt::entity playerEntity)
{
	m_playerEntity = playerEntity;
}

void InputManager::SetProjectileEntity(entt::entity projectileEntity)
{
	m_playerEntity = m_projectileEntity;
}
