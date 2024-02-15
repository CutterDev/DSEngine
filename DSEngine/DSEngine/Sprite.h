#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
#include "Shader.h"
#include "ResourceManager.h"

#include <iostream>
class Sprite
{
    unsigned int m_QuadVAO;
    Texture2D* m_Texture;
    glm::vec3 m_Color;
    Shader* m_Shader;

public:
    void Initialize(const char* path, bool alpha, Shader* shader);
    void Draw();
    void Destroy();
};

