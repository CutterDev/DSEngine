#pragma once
#include <string>
#include <vector>
#include <unordered_map>


#include "SpriteComponent.h"

struct Entity {
    unsigned int EntityId;

    glm::vec2 Position = glm::vec2(0.f);
    glm::vec2 Scale = glm::vec2(1.f);
    float Rotation = 0.f;

    glm::mat4 GetTransform()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(Position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

        model = glm::rotate(model, glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate

        model = glm::scale(model, glm::vec3(Scale, 1.0f)); // last scale

        return model;
    }
};

class EntityManager
{
private:
    unsigned int m_Amount;
    std::unordered_map<std::string, int> m_EntityIndex;
    std::vector<Entity> m_Entity;

    std::map<int, std::string> m_SpriteIndex; // String: Entity Name -> String: Sprite Name
    std::map<std::string, SpriteComponent> m_SpriteComponents; // Many Components -> One Sprite

public:
    Entity CreateEntity(std::string name);
    void CreateSprite(Entity entity, std::string spriteName);
    void Start();
    void UpdateTransform(Entity entity);
    void RemoveEntity(Entity entity);
    void Update(glm::mat4 projection, glm::mat4 view);
    void Destroy();
};

