#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "MeshFilter.h"

class DefaultCube : public MeshFilter
{
private:
    unsigned int m_VAO, m_VBO;
public:
    DefaultCube();
    ~DefaultCube();
    void Draw();
};

