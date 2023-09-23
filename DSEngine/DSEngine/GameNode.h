#pragma once
#include "GameCamera.h"

class GameObject;

class GameNode
{
public:
    GameNode() {}
    virtual ~GameNode() {}
    virtual void Update(GameCamera* camera, GameObject* gameObject) = 0;    // "= 0" part makes this method pure virtual, and
};

class BasicCubeNode;
