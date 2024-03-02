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

struct SpriteData {
   alignas(16) glm::vec3 Position;
   alignas(16) glm::vec3 Color;
   alignas(8) glm::vec2 Scale;
   alignas(8) float Rotation;
};
class Sprite
{
    int Amount;
    unsigned int VAO, VBO, EBO;
    unsigned int DataBuffer;
    Texture2D m_Texture;
    Shader m_Shader;
    std::vector<SpriteData> Instances;
    std::vector<glm::vec3> Positions;
    std::vector<glm::vec3> Colors;
    std::vector<glm::vec2> Scales;
    std::vector<float> Rotations;

    std::map<unsigned int, int> InstanceIndex;
public:
    void Startup(const char* path, bool alpha, std::string shader = "sprite");
    void Initialize();
    void AddNewInstance(unsigned int entityId,
        glm::vec3 pos = glm::vec3(0.f),
        glm::vec2 scale = glm::vec2(1.f),
        glm::vec3 color = glm::vec3(1.f),
        float rotation = 0.f);
    void UpdatePosition(unsigned int entityId, glm::vec3 pos);
    void Draw(glm::mat4 projection, glm::mat4 view);
    void Destroy();
};

