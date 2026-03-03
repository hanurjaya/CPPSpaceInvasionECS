#include "EntityRegistryManager.h"

EntityRegistryManager* EntityRegistryManager::m_ERMInstance = nullptr;

EntityRegistryManager::EntityRegistryManager()
{
}

entt::entity EntityRegistryManager::CreateNewEntity()
{
	return m_registry.create();
}

entt::registry* EntityRegistryManager::GetRegistry()
{
	return &m_registry;
}

EntityRegistryManager::~EntityRegistryManager()
{
	m_registry.~basic_registry();
}

EntityRegistryManager* EntityRegistryManager::GetInstance()
{
	if (m_ERMInstance == nullptr)
	{
		m_ERMInstance = new EntityRegistryManager();
	}
	return m_ERMInstance;
}