#pragma once
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <memory>
#include "IComponent.h"

class Entity
{
public:
    glm::vec2 Position;
    float Rotation;
    glm::vec2 Size; // Not a scale.
private:
    std::string m_Name;
    std::vector<std::shared_ptr<IComponent>> m_Components;
public:
    Entity(std::string name);
    void AddComponent(std::shared_ptr<IComponent> component);
    void RemoveComponent(IComponent component);
    void UpdateComponents();

};