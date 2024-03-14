#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <b2_math.h>

#include "CommonHeaders.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "TileManager.h"
#include "EntityManager.h"

#include "MainGameScene.h"
#include "GameCamera.h"



struct Window {
    float Width;
    float Height;
    float AspectRatio;
};

class Game
{
private:
    GameCamera* m_MainCamera;
    Window m_Window;
    Mouse m_Mouse;

    glm::vec3 spritePosition;
    glm::mat4 spriteTransform;

    bool updatePos;
    void SetupInput();
public:
    void Initialize(unsigned int width, unsigned int height);
    void Tick(float deltaTime);
    void PollInputs(GLFWwindow* window);
    void PollMouseInput(double x, double y);
    void FrameSizeChanged(int width, int height);
    void Shutdown();
};

