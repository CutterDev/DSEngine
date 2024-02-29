#pragma once
#include "IComponent.h"
#include "Sprite.h"
#include "Shader.h"
#include "GameCamera.h"

class SpriteComponent : public IComponent
{


public:
    glm::mat4 Model;
    glm::vec3 Color;
    Shader* SpriteShader;
    unsigned int VAO;
    unsigned int TexCoordsBuffer;
    unsigned int PositionsBuffer;
    std::vector<glm::ivec2> Offsets;
    SpriteComponent(Entity* entity, glm::vec3 color = glm::vec3(1.0f));
    void Start() override;
    void Update() override;
    void End() override;
};

