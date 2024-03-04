#pragma once
#include <glm/glm.hpp>
struct Light {
    unsigned int EntityId;
    glm::vec4 LightColor;
    float Distance;
    glm::vec2 LightPos = glm::vec2(0.f);
};