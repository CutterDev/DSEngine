#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "SpriteComponent.h"
#include "LightComponent.h"

#include <b2_world.h>
#include <b2_polygon_shape.h>
#include <b2_body.h>

struct Entity {
    unsigned int EntityId;
    
    glm::vec2 Position = glm::vec2(0.f);
    glm::vec2 Scale = glm::vec2(1.f);
    float Rotation = 0.f;

    /// <summary>
    /// Keep Alive if scene dies.
    /// </summary>
    bool KeepAlive = false;

    glm::mat4 GetTransform()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(Position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

        model = glm::rotate(model, Rotation, glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate

        model = glm::scale(model, glm::vec3(Scale, 1.0f)); // last scale

        return model;
    }
};

class EntityManager
{
private:
    unsigned int m_Amount;
    std::unordered_map<std::string, int> m_EntityIndex;
    std::vector<Entity> m_Entities;

    std::map<int, std::string> m_SpriteIndex; // String: Entity Name -> String: Sprite Name
    std::map<std::string, SpriteComponent> m_SpriteComponents; // Many Components -> One Sprite
    std::map<unsigned int, int> m_LightIndex;
    std::vector<Light> m_LightComponents;

    std::map<int, b2Body*> m_Bodies;

    EntityManager() : m_Amount(0) {}
public:
    // Singleton
    ////////////////////
    static EntityManager& Instance()
    {
        static EntityManager instance;
        
        return instance;
    }
    EntityManager(EntityManager const&) = delete;
    void operator=(EntityManager const&) = delete;
    //
    ////////////////////

    Entity CreateEntity(std::string name, glm::vec2 pos = glm::vec2(0.f), glm::vec2 scale = glm::vec2(1.f), float rot = 0.f);
    void CreateSprite(Entity entity, std::string spriteName);
    void CreateLight(unsigned int entityid, glm::vec3 color = glm::vec3(1.f), float intensity = 1.f, float distance = 10.f);
    void CreateBody(b2World* world, Entity entity);
    void Start();
    void UpdateTransform(Entity entity);
    std::vector<Light> GetLights();
    void RemoveEntity(Entity entity);
    void Update(glm::mat4 projection, glm::mat4 view);
    void Destroy();
};


#ifndef ENTITY_FUNCS
#define ENTITY_FUNCS
Entity createEntity(std::string name, glm::vec2 pos = glm::vec2(0.f), glm::vec2 scale = glm::vec2(1.f), float rot = 0.f);
void createSprite(Entity entity, std::string spriteName);
void createLight(unsigned int entityid, glm::vec3 color = glm::vec3(1.f), float intensity = 1.f, float distance = 10.f);
#define NewEntity(name, pos, scale, rot) createEntity(name, pos, scale, rot)
#endif