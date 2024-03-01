#include "Game.h"

void Game::SetupInput()
{
    m_Input.AddAction("Exit", GLFW_KEY_ESCAPE);
    m_Input.AddAction("MoveUp", GLFW_KEY_W);
    m_Input.AddAction("MoveDown", GLFW_KEY_S);
    m_Input.AddAction("MoveLeft", GLFW_KEY_A);
    m_Input.AddAction("MoveRight", GLFW_KEY_D);
    m_Input.AddAction("Delete", GLFW_KEY_H);
    m_Input.AddAction("Create", GLFW_KEY_F);
}

void Game::Initialize()
{
    m_TileManager = new TileManager("blocks.png", 16, 0);

    SetupInput();


}

void Game::Tick(float deltaTime)
{

}

void Game::PollInputs(GLFWwindow* window)
{
    m_Input.PollInputs(window);
    if (m_Input.IsPressedDown("Exit"))
    {
        glfwSetWindowShouldClose(window, true);
    }
}
