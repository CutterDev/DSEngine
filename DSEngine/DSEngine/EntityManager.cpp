#include "EntityManager.h"

void EntityManager::AddEntity(Entity* entity)
{
    m_Entities.push_back(entity);
}

void EntityManager::RemoveEntity(Entity entity)
{
    //m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entity), m_Entities.end());
}

void EntityManager::Update()
{
    for (Entity* entity : m_Entities)
    {
        entity->UpdateComponents();
    }
}