#include "MainGameScene.h"
#include "InputManager.h"

// Create Entities and Components for the Scene
void MainGameScene::OnCreate(GameCamera* camera, Mouse* mouse)
{
    m_MainCamera = camera;
    m_Mouse = mouse;
    m_TileManager.Startup("blocks.png", 16, 0);

    m_Entity = NewEntity("sprite", glm::vec2(0.f), glm::vec2(20.f), 45.f);

    EntityManager::Instance().CreateSprite(m_Entity, "wall.jpg");
    EntityManager::Instance().CreateLight(m_Entity.EntityId, glm::vec3(1.f), 0.8f, 200.f);
}


void MainGameScene::OnActivate()
{
    for (int y = -100; y < 100; y++)
    {
        for (int x = -1000; x < 1000; x++)
        {
            int id = 2;

            m_TileManager.SetTile(id, glm::ivec2(x, y));
        }
    }

    // Load The Create Scenes Entities Sprites
    EntityManager::Instance().Start();
    m_TileManager.Populate();
}


void MainGameScene::Update(float deltaTime)
{
    bool updatePos = false;
    float speed = deltaTime * 50.f;
    if (InputManager::IsPressed("MoveUp"))
    {
        //m_MainCamera.Translate(speed * glm::vec3(0.f, -1.f, 0.f));
        m_Entity.Position.y += speed;
        updatePos = true;
    }

    if (InputManager::IsPressed("MoveDown"))
    {
        //m_MainCamera.Translate(speed * glm::vec3(0.f, 1.f, 0.f));
        m_Entity.Position.y -= speed;
        updatePos = true;
    }


    if (InputManager::IsPressed("MoveLeft"))
    {
        //m_MainCamera.Translate(-speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        m_Entity.Position.x -= speed;
        updatePos = true;
    }

    if (InputManager::IsPressed("MoveRight"))
    {
        //m_MainCamera.Translate(speed * glm::cross(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)));
        m_Entity.Position.x += speed;

        updatePos = true;
    }

    if (InputManager::IsPressed("RotateLeft"))
    {
        updatePos = true;
        m_Entity.Rotation += speed;
    }
    if (InputManager::IsPressed("RotateRight"))
    {
        updatePos = true;
        m_Entity.Rotation -= speed;
    }

    if (updatePos)
    {
        EntityManager::Instance().UpdateTransform(m_Entity);
    }

    if (InputManager::IsPressed("Delete"))
    {
        glm::vec3 worldPos = m_MainCamera->ScreenToWorldPos(m_Mouse->Position);

        glm::ivec2 tilePos = m_TileManager.GetTileFromWorldPos(worldPos);
        std::cout << glm::to_string(worldPos) << std::endl;
        m_TileManager.SetTile(-1, tilePos);
    }

    if (InputManager::IsPressed("Create"))
    {
        glm::vec3 worldPos = m_MainCamera->ScreenToWorldPos(m_Mouse->Position);
        glm::ivec2 tilePos = m_TileManager.GetTileFromWorldPos(worldPos);
        m_TileManager.SetTile(65, tilePos);
    }


    m_MainCamera->Update();
}

void MainGameScene::Draw(float deltaTime)
{
    EntityManager::Instance().Update(m_MainCamera->Projection, m_MainCamera->View);

    std::vector<Light> lights = EntityManager::Instance().GetLights();

    for (int i = 0; i < lights.size(); i++)
    {
        lights[i].LightPos = m_MainCamera->WorldPosToScreenSpace(glm::vec3(lights[i].LightPos, 1.f));
    }

    m_TileManager.Draw(m_MainCamera->Projection, m_MainCamera->View, lights);


}

void MainGameScene::OnDestroy()
{
    m_TileManager.Destroy();
}


void MainGameScene::OnDeactivate()
{
}

