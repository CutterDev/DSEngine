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
    m_Input.AddAction("RotateLeft", GLFW_KEY_Q);
    m_Input.AddAction("RotateRight", GLFW_KEY_E);
}

void Game::Initialize(unsigned int width, unsigned int height)
{
    m_Window = { (float)width, (float)height, (float)width / (float)height };
    m_TileManager.Startup("blocks.png", 16, 0);
    
    SetupInput();

    m_MainCamera.SetProjection(m_Window.Width, m_Window.Height, m_Window.AspectRatio);

    // Add the Scenes/Entities/Sprites

    m_Entity = m_EntityManager.CreateEntity("sprite");
    m_Entity.Position = glm::vec3(10.0f, 0.0f, 0.0f);
    m_Entity.Rotation = 45;
    m_Entity.Scale = glm::vec2(20.f);

    m_EntityManager.CreateSprite(m_Entity, "wall.jpg");

    for (int y = -100; y < 100; y++)
    {
        for (int x = -1000; x < 1000; x++)
        {
            int id = 2;

            m_TileManager.SetTile(id, glm::ivec2(x, y));
        }
    }

    // Load The Create Scenes Entities Sprites
    m_EntityManager.Start();
    m_TileManager.Initialize();
}

void Game::Tick(float deltaTime)
{
    float speed = deltaTime * 50.f;
    if (m_Input.IsPressed("MoveUp"))
    {
        //m_MainCamera.Translate(speed * glm::vec3(0.f, -1.f, 0.f));
        m_Entity.Position.y += speed;
        updatePos = true;
    }

    if (m_Input.IsPressed("MoveDown"))
    {
        //m_MainCamera.Translate(speed * glm::vec3(0.f, 1.f, 0.f));
        m_Entity.Position.y -= speed;
        updatePos = true;
    }


    if (m_Input.IsPressed("MoveLeft"))
    {
        //m_MainCamera.Translate(-speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        m_Entity.Position.x -= speed;
        updatePos = true;
    }

    if (m_Input.IsPressed("MoveRight"))
    {
        //m_MainCamera.Translate(speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        m_Entity.Position.x += speed;

        updatePos = true;
    }

    if (m_Input.IsPressed("RotateLeft"))
    {
        updatePos = true;
        m_Entity.Rotation += speed;
    }
    if (m_Input.IsPressed("RotateRight"))
    {
        updatePos = true;
        m_Entity.Rotation -= speed;
    }
    if (updatePos)
    {
        m_EntityManager.UpdateTransform(m_Entity);
    }

    m_MainCamera.Update(m_Window.Width, m_Window.Height);

    if (m_Input.IsPressed("Delete"))
    {
        glm::vec3 worldPos = m_MainCamera.ScreenToWorldPos(m_Mouse.Position);

        glm::ivec2 tilePos = m_TileManager.GetTileFromWorldPos(worldPos);
        std::cout << glm::to_string(worldPos) << std::endl;
        m_TileManager.SetTile(-1, tilePos);
    }

    if (m_Input.IsPressed("Create"))
    {
        glm::vec3 worldPos = m_MainCamera.ScreenToWorldPos(m_Mouse.Position);
        glm::ivec2 tilePos = m_TileManager.GetTileFromWorldPos(worldPos);
        m_TileManager.SetTile(65, tilePos);
    }

    m_EntityManager.Update(m_MainCamera.Projection, m_MainCamera.View);
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
    m_Window.AspectRatio = m_Window.Width / m_Window.Height;

    m_MainCamera.SetProjection(m_Window.Width, m_Window.Height, m_Window.AspectRatio);
}

void Game::Shutdown()
{
    m_TileManager.Destroy();
    sprite.Destroy();
}
