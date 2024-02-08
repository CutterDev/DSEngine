#pragma once
#include <vector>

#include "Entity.h"

class EntityManager
{
private:
    std::vector<Entity> m_Entities;
public:
    void AddEntity(Entity entity);
    void RemoveEntity(Entity entity);
    void Update();
};

