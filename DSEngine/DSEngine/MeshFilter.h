#pragma once
#include "GameCamera.h"
#include "gameobject.h"
class MeshFilter
{
public:
    MeshFilter() { };
    ~MeshFilter() { };
    virtual void Draw() = 0;
};

