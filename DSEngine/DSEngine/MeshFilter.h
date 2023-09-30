#pragma once
#include "GameCamera.h"
#include "gameobject.h"
#include <iostream>
class MeshFilter
{
public:
    MeshFilter() { };
    MeshFilter(const char* path);
    ~MeshFilter() { };
    virtual void Draw() = 0;
};

