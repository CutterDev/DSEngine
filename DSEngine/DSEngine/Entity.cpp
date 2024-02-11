#include "Entity.h"
Entity::Entity(std::string name)
{
    m_Name = name;
    Position = glm::vec2(0.f);
    Size = glm::vec2(1.f);
}

void Entity::AddComponent(IComponent& component)
{
    m_Components.push_back(std::shared_ptr<IComponent>(&component));
}

void Entity::UpdateComponents()
{
    for (std::shared_ptr<IComponent> component : m_Components)
    {
        component->Update();
    }
}