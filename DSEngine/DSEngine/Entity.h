#pragma once
#include <glm/glm.hpp>

#include <vector>

#include "IComponent.h"

class Entity
{
public:
    alignas(16) glm::mat4 Transform;
private:
    std::vector<IComponent> m_Components;
public:
    void AddComponent(IComponent component);
    void RemoveComponent(IComponent component);
    void UpdateComponents();

};