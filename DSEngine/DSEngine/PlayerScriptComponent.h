#pragma once
#include "IComponent.h"

class PlayerScriptComponent: public IComponent
{
    // Inherited via IComponent
    void Start() override;
    void Update(float deltaTime) override;
    void End() override;
};

