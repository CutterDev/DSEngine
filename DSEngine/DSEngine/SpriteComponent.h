#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
#include "Shader.h"
#include "ResourceManager.h"
#include <iostream>
#include <vector>
#include <string>

template <typename T>
struct SpriteData {
    bool HasResized;
    bool HasUpdated;
    std::vector<T> Data;

    size_t Size()
    {
        return sizeof(T) * Data.size();
    }

    void ResetFlags()
    {
        HasResized = false;
        HasUpdated = false;
    }
};
class SpriteComponent
{
    int Amount;
    unsigned int VAO, VBO, EBO;
    unsigned int DataBuffer;
    Texture2D m_Texture;
    Shader m_Shader;

    SpriteData<glm::mat4> Transforms;
    SpriteData<glm::vec3> Colors;

    std::map<unsigned int, int> InstanceIndex;

    void Bind();
    void CheckForUpdates();
    void AllocateMemory();
    void UpdateTransforms();
    void UpdateColors();
public:
    void Startup(const char* path, bool alpha, std::string shader = "sprite");
    void Initialize();
    void AddNewInstance(unsigned int spriteId,
        glm::mat4 transform = glm::mat4(1.f),
        glm::vec3 color = glm::vec3(1.f));
    void UpdateTransform(unsigned int spriteId, glm::mat4 transform);
    void Draw(glm::mat4 projection, glm::mat4 view);
    void Destroy();
};

