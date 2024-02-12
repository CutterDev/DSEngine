#pragma once
#include "IComponent.h"
#include "DSCore.h"
#include "Sprite.h"
#include "Shader.h"
#include "GameCamera.h"

class SpriteComponent : public IComponent
{
    Sprite* m_Sprite;
    Shader* m_Shader;
    glm::vec3 m_Color;
public:
    SpriteComponent(Entity* entity, glm::vec3 color = glm::vec3(1.0f));
    void Start() override;
    void AssignSprite(Sprite* sprite);
    void AssignShader(Shader* shader);
    void Update() override;
    void End() override;
};

