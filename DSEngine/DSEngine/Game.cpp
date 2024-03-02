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

void Game::Initialize(unsigned int width, unsigned int height)
{
    m_Window = { (float)width, (float)height };
    m_TileManager.Startup("blocks.png", 16, 0);
    SetupInput();

    m_MainCamera.SetProjection(glm::ortho(
        0.0f,
        (float)width,
        (float)height,
        0.0f,
        0.1f,
        10.0f));

    // Add the Scenes/Entities/Sprites

    unsigned int entity = 1;
    unsigned int entity1 = 2;

    sprite.Startup("wall.jpg", false);
    sprite.AddNewInstance(entity, spritePos, glm::vec2(1.f), glm::vec3(0.f, 1.0f, 0.f));
    sprite.AddNewInstance(entity1, glm::vec3(10.f, 3.f, 0.0f));

    for (int y = -10; y < 10; y++)
    {
        for (int x = -10; x < 10; x++)
        {
            int id = 1;

            if (x == 0 && y == 0 ||
                x == 0 && y == -1 ||
                x == -1 && y == 0 ||
                x == -1 && y == -1)
            {
                id = 35;
            }

            m_TileManager.SetTile(id, glm::ivec2(x, y));
        }
    }

    // Load The Create Scenes Entities Sprites
    m_TileManager.Initialize();
    sprite.Initialize();
}

void Game::Tick(float deltaTime)
{
    float speed = deltaTime * 50.f;
    if (m_Input.IsPressed("MoveUp"))
    {
        //m_MainCamera.Translate(speed * glm::vec3(0.f, -1.f, 0.f));
        spritePos.y += -speed;
    }

    if (m_Input.IsPressed("MoveDown"))
    {
        //m_MainCamera.Translate(speed * glm::vec3(0.f, 1.f, 0.f));
        spritePos.y  += speed;
    }

    if (m_Input.IsPressed("MoveLeft"))
    {
        //m_MainCamera.Translate(-speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        spritePos.x += -speed;
    }

    if (m_Input.IsPressed("MoveRight"))
    {
        //m_MainCamera.Translate(speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        spritePos.x += speed;
    }
     

    sprite.UpdatePosition(2, spritePos);
    m_MainCamera.Update(m_Window.Width, m_Window.Height);

    if (m_Input.IsPressedUp("Delete"))
    {
        glm::vec3 worldPos = m_MainCamera.ScreenToWorldPos(m_Mouse.Position);

        glm::ivec2 tilePos = m_TileManager.GetTileFromWorldPos(worldPos);
        std::cout << glm::to_string(worldPos) << std::endl;
        m_TileManager.SetTile(-1, tilePos);
    }

    if (m_Input.IsPressedUp("Create"))
    {
        glm::vec3 worldPos = m_MainCamera.ScreenToWorldPos(m_Mouse.Position);
        glm::ivec2 tilePos = m_TileManager.GetTileFromWorldPos(worldPos);
        m_TileManager.SetTile(6, tilePos);
    }

    m_TileManager.Draw(m_MainCamera.Projection, m_MainCamera.View);
    sprite.Draw(m_MainCamera.Projection, m_MainCamera.View);
}

void Game::PollInputs(GLFWwindow* window)
{
    m_Input.PollInputs(window);
    if (m_Input.IsPressedDown("Exit"))
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
}

void Game::Shutdown()
{
    m_TileManager.Destroy();
    sprite.Destroy();
}
