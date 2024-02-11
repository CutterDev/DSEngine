#pragma once

class Entity;

class IComponent
{
protected:
    Entity* p_Entity; // Entity Component is tied to.
public:
    IComponent(Entity* entity);
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void End() = 0;
};

