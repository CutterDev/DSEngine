#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include <iostream>
#include <vector>
#include <string>

class Sprite
{
    int Amount;
    unsigned int VAO, VBO, EBO;
    unsigned int DataBuffer;
    Texture2D m_Texture;
    Shader m_Shader;
    std::vector<glm::mat4> Transforms;
    std::vector<glm::vec3> Colors;
    std::vector<glm::vec2> Scales;
    std::vector<float> Rotations;

    std::map<unsigned int, int> InstanceIndex;
public:
    void Startup(const char* path, bool alpha, std::string shader = "sprite");
    void Initialize();
    void AddNewInstance(unsigned int entityId,
        glm::mat4 transform = glm::mat4(1.f),
        glm::vec3 color = glm::vec3(1.f));
    void UpdatePosition(unsigned int entityId, glm::mat4 transform);
    void Draw(glm::mat4 projection, glm::mat4 view);
    void Destroy();
};

