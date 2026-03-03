#pragma once
#include <entt.hpp>

class EntityRegistryManager
{
private:
	EntityRegistryManager();
	static EntityRegistryManager* m_ERMInstance;
	entt::registry m_registry;
public:
	EntityRegistryManager(EntityRegistryManager&) = delete;
	void operator=(const EntityRegistryManager&) = delete;
	static EntityRegistryManager* GetInstance();
	entt::entity CreateNewEntity();
	entt::registry* GetRegistry();
	~EntityRegistryManager();
};

