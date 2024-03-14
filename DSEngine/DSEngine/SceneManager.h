#pragma once
#include <map>
#include "Scene.h"
#include <string>
class SceneManager
{
private:
    std::string m_CurrentScene = ""; // index

public:
    std::map<std::string, Scene*> Scenes;

    SceneManager() { }

    void Startup(GameCamera* camera, Mouse* mouse, std::string firstScene);
    void SetCurrentScene(std::string name);
    void Update(float deltaTime);
    void Shutdown();

    // Singleton
    ////////////////////
    static SceneManager& Instance()
    {
        static SceneManager instance;

        return instance;
    }
    SceneManager(SceneManager const&) = delete;
    void operator=(SceneManager const&) = delete;
    //
    ////////////////////
};