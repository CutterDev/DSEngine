#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "GameCamera.h"

class Material
{
public:
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    float Shininess;
    Shader* Shader;

    void Use(const GameCamera* camera, const glm::mat4& gameObject) const;
};

