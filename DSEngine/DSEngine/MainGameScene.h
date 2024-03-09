#pragma once
#include "GameCamera.h"
#include "Scene.h"
#include "TileManager.h"
#include "CommonHeaders.h"
#include "EntityManager.h"

class MainGameScene : public Scene
{
    EntityManager m_EntityManager;
    TileManager m_TileManager;
    GameCamera* m_MainCamera;
    Entity m_Entity;
    Mouse* m_Mouse;
    // Inherited via Scene
    void OnCreate(GameCamera* camera, Mouse* mouse) override;
    void OnDestroy() override;

    // Inherited via Scene
    void OnActivate() override;
    void OnDeactivate() override;
    void Update(float deltaTime) override;
    void Draw(float deltaTime) override;
};

