#pragma once

class Entity;

class IComponent
{
public:
    Entity* p_Entity;
    IComponent(Entity* entity);
    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void End() = 0;
};

