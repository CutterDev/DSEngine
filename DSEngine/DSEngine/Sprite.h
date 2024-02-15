#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
#include "Shader.h"
#include "ResourceManager.h"

#include <iostream>
#include <vector>

class SpriteComponent;

class Sprite
{

    Texture2D* m_Texture;
    glm::vec3 m_Color;
    Shader* m_Shader;
    std::vector<SpriteComponent*> m_Instances;
public:
    void Initialize(const char* path, bool alpha, Shader* shader);
    void Draw();
    void AddInstance(SpriteComponent* entity);
    void Destroy();
};

