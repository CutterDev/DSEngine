#include "EntityManager.h"

Entity EntityManager::CreateEntity(std::string name)
{
    if (m_EntityIndex.find(name) == m_EntityIndex.end())
    {
        Entity entity = {
            m_Amount
        };

        m_Amount++;

        return entity;
    }


    return Entity();
}

void EntityManager::CreateSprite(Entity entity, std::string spriteName)
{
    if (m_SpriteComponents.find(spriteName) == m_SpriteComponents.end())
    {
        m_SpriteComponents[spriteName] = SpriteComponent();
        m_SpriteComponents[spriteName].Startup(spriteName.c_str(), false);
    }
    
    m_SpriteIndex[entity.EntityId] = spriteName;
    m_SpriteComponents[spriteName].AddNewInstance(entity.EntityId, entity.GetTransform());
}

void EntityManager::Start()
{
    for (std::map<std::string, SpriteComponent>::iterator it = m_SpriteComponents.begin(); it != m_SpriteComponents.end(); ++it)
    {
        it->second.Initialize();
    }
}

void EntityManager::UpdateTransform(Entity entity)
{
    std::string sprite = m_SpriteIndex[entity.EntityId];

    if (m_SpriteComponents.find(sprite) != m_SpriteComponents.end())
    {
        m_SpriteComponents[sprite].UpdateTransform(entity.EntityId, entity.GetTransform());
    }
}

void EntityManager::Update(glm::mat4 projection, glm::mat4 view)
{
    for (std::map<std::string, SpriteComponent>::iterator it = m_SpriteComponents.begin(); it != m_SpriteComponents.end(); ++it)
    {
        it->second.Draw(projection, view);
    }
}

void EntityManager::Destroy()
{
    for (std::map<std::string, SpriteComponent>::iterator it = m_SpriteComponents.begin(); it != m_SpriteComponents.end(); ++it)
    {
        it->second.Destroy();
    }
}


