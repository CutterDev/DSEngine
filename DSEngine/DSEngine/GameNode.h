#pragma once
#include "GameCamera.h"

class GameObject;

class GameNode
{
public:
    GameObject* GameObject;
    GameNode() {}
    virtual ~GameNode() {}
    virtual void Update(GameCamera* camera) = 0;    // "= 0" part makes this method pure virtual, and
};

class BasicCubeNode;
