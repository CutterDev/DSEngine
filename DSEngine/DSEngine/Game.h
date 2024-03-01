#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "InputManager.h"

#include "TileManager.h"
#include "GameCamera.h"


class Game
{
private:
    GameCamera m_MainCamera;
    InputManager m_Input;
    TileManager* m_TileManager;
    Sprite Sprite("wall.jpg", false);
    void SetupInput();
public:
    void Initialize();
    void Tick(float deltaTime);
    void PollInputs(GLFWwindow* window);
};

