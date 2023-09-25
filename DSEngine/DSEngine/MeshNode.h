#pragma once

#include "GameNode.h"
#include "MeshFilter.h"
#include "Material.h"

class MeshNode : public GameNode
{
public:
    Material* Material;
    MeshFilter* MeshFilter;
    MeshNode() {}
    ~MeshNode() {};
    void Update(GameCamera* camera);
};

