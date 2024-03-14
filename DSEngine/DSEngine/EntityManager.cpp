#include "EntityManager.h"

Entity createEntity(std::string name, glm::vec2 pos, glm::vec2 scale, float rot)
{
    return EntityManager::Instance().CreateEntity(name, pos, scale, rot);
}

Entity EntityManager::CreateEntity(std::string name, glm::vec2 pos, glm::vec2 scale, float rot)
{
    if (m_EntityIndex.find(name) == m_EntityIndex.end())
    {
        Entity entity = {
            m_Amount,
            pos,
            scale,
            rot
        };

        m_EntityIndex[name] = m_Amount;

        m_Entities.push_back(entity);
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

void EntityManager::CreateLight(unsigned int entityid, glm::vec3 color, float intensity,  float distance)
{
    if (m_LightIndex.find(entityid) == m_LightIndex.end())
    {
        m_LightIndex[entityid] = m_LightComponents.size();
        Entity entity = m_Entities[entityid];

        m_LightComponents.push_back({ entity.EntityId, glm::vec4(color, intensity), distance, entity.Position });
    }
}

void EntityManager::CreateBody(b2World* world, Entity entity)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((entity.Position.x * entity.Scale.x) * 0.02f, (entity.Position.y * entity.Scale.y) * 0.02f);
    m_Bodies[entity.EntityId] = world->CreateBody(&bodyDef);
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

    m_Entities[entity.EntityId] = entity;
    if (m_SpriteComponents.find(sprite) != m_SpriteComponents.end())
    {
        m_SpriteComponents[sprite].UpdateTransform(entity.EntityId, entity.GetTransform());
    }

    if (m_LightIndex.find(entity.EntityId) != m_LightIndex.end())
    {
        int index = m_LightIndex[entity.EntityId];

        m_LightComponents[index].LightPos = entity.Position;
    }
}

std::vector<Light> EntityManager::GetLights()
{
    return m_LightComponents;
}

void EntityManager::Update(glm::mat4 projection, glm::mat4 view)
{
    for (std::map<std::string, SpriteComponent>::iterator it = m_SpriteComponents.begin(); it != m_SpriteComponents.end(); ++it)
    {
        it->second.Draw(projection, view);
    }
}

/// <summary>
/// Called when scene is destroyed
/// </summary>
void EntityManager::Destroy()
{
    for (std::vector<Entity>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it)
    {
        if (!it->KeepAlive)
        {
            std::string sprite = m_SpriteIndex[it->EntityId];

            if (m_SpriteComponents.find(sprite) != m_SpriteComponents.end())
            {
                // remove entity m_SpriteComponents[sprite]
                m_SpriteComponents[sprite].RemoveInstance(it->EntityId);
            }
        }
    }
}


