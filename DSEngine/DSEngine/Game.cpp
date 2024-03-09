#include "Game.h"
#include "LightComponent.h"
/// <summary>
/// Set up Input for the Game
/// </summary>
void Game::SetupInput()
{
    InputManager::AddAction("Exit", GLFW_KEY_ESCAPE);
    InputManager::AddAction("MoveUp", GLFW_KEY_W);
    InputManager::AddAction("MoveDown", GLFW_KEY_S);
    InputManager::AddAction("MoveLeft", GLFW_KEY_A);
    InputManager::AddAction("MoveRight", GLFW_KEY_D);
    InputManager::AddAction("Delete", GLFW_KEY_H);
    InputManager::AddAction("Create", GLFW_KEY_F);
    InputManager::AddAction("RotateLeft", GLFW_KEY_Q);
    InputManager::AddAction("RotateRight", GLFW_KEY_E);
}


/// <summary>
/// Initializer the Modules of the Game 
/// TODO: ADD SCENE MANAGER INTO THE GAME 
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Game::Initialize(unsigned int width, unsigned int height)
{
    m_Window = { (float)width, (float)height, (float)width / (float)height };

    mainGameScene = new MainGameScene();
    m_MainCamera = new GameCamera();
    SetupInput();

    m_MainCamera->Initialize(width, height);
    m_MainCamera->SetProjection(m_Window.Width, m_Window.Height, m_Window.AspectRatio);
    mainGameScene->OnCreate(m_MainCamera, &m_Mouse);

    mainGameScene->OnActivate();
    // Add the Scenes/Entities/Sprites

}

void Game::Tick(float deltaTime)
{
    mainGameScene->Update(deltaTime);

    mainGameScene->Draw(deltaTime);
}

void Game::PollInputs(GLFWwindow* window)
{
    InputManager::PollInputs(window);
    if (InputManager::IsPressedDown("Exit"))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Game::PollMouseInput(double x, double y)
{
    m_Mouse.Position = glm::vec2(x, y);
}

void Game::FrameSizeChanged(int width, int height)
{
    m_Window.Width = width;
    m_Window.Height = height;
    m_Window.AspectRatio = m_Window.Width / m_Window.Height;

    m_MainCamera->SetProjection(m_Window.Width, m_Window.Height, m_Window.AspectRatio);
}

void Game::Shutdown()
{
}
