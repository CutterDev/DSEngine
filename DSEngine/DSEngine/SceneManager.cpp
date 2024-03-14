#include "SceneManager.h"

/// <summary>
/// First Current Scene runs
/// </summary>
void SceneManager::Startup(GameCamera *camera, Mouse *mouse, std::string firstScene)
{
    m_CurrentScene = firstScene;

    for (const auto& kv : Scenes) {
        kv.second->OnCreate(camera, mouse);
    }

    Scenes[m_CurrentScene]->OnActivate();
}

void SceneManager::SetCurrentScene(std::string name)
{
    Scenes[m_CurrentScene]->OnDeactivate();
    
    m_CurrentScene = name;

    Scenes[m_CurrentScene]->OnActivate();
}

void SceneManager::Update(float deltaTime)
{
    Scenes[m_CurrentScene]->Update(deltaTime);
    Scenes[m_CurrentScene]->Draw(deltaTime);
}

void SceneManager::Shutdown()
{
    for (const auto& kv : Scenes) {
        kv.second->OnDestroy();
    }
}
