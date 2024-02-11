#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Texture2D.h"
#include "Shader.h"
#include "stb_image.h"

#include <iostream>
class Sprite
{
    unsigned int m_QuadVAO;
    Texture2D m_Texture;
    glm::vec3 m_Color;
    Shader* m_Shader;

public:
    void Initialize(const char* path, bool alpha, Shader* shader);
    void Draw();
    void Destroy();
};

