#pragma once
#include "Shader.h"
#include "GameNode.h"

class BasicCubeNode : public GameNode
{
private:


public:
    unsigned int m_VAO, m_VBO;
    Shader* m_Shader = NULL;

    BasicCubeNode();
    ~BasicCubeNode();
    void Update(GameCamera* camera);
};

