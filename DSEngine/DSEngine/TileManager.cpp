#include "TileManager.h"

TileManager::TileManager(std::string texture, unsigned int tileSize, int tileSetSpacing)
{
    m_TileSize = tileSize;
    m_TileSpacing = tileSetSpacing;
    m_AtlasTileSize = tileSize + tileSetSpacing;

    m_Shader = new Shader("tile.vs", "tile.fs", "tile.gs");

    m_Shader->Use();
    m_Shader->SetInt("tilesheet", 0);

    tileAtlas = ResourceManager::GetInstance().GetTexture(texture, true);
    m_AtlasTilesX = tileAtlas->Width / (tileSize + tileSetSpacing);
    m_AtlasTilesY = tileAtlas->Height / (tileSize + tileSetSpacing);


    m_TileSetCoords[m_AtlasTilesX * m_AtlasTilesY];

    int tileId = 0;

    for (int y = 0; y < m_AtlasTilesY; y++)
    {
        for (int x = 0; x < m_AtlasTilesX; x++)
        {
            m_TileSetCoords[tileId] = TileCoords{
                // Top Right
                glm::vec2(m_AtlasTileSize + (m_AtlasTileSize * x),
                tileSetSpacing +(m_AtlasTileSize * y)),
                // Bottom Right
                glm::vec2(m_AtlasTileSize + (m_AtlasTileSize * x),
                m_AtlasTileSize + (m_AtlasTileSize * y)),
                // Bottom Left
                glm::vec2(tileSetSpacing + (m_AtlasTileSize * x),
                m_AtlasTileSize + (m_AtlasTileSize * y)),

                // Top Left
                glm::vec2(tileSetSpacing + (m_AtlasTileSize * x),
                tileSetSpacing + (m_AtlasTileSize * y))
            };

            tileId++;
        }
    }
}

void TileManager::Initialize()
{
    std::size_t vec4Size = sizeof(glm::vec4);

    unsigned int buffer;
    glGenBuffers(1, &buffer);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    int dataSize = 10 * sizeof(float);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, m_Tiles.size(),
        &m_Tiles[0],
        GL_STATIC_DRAW);
    std::cout << glGetError() << std::endl;
    // Tex // Top Right // Bottom Right
    glEnableVertexAttribArray(0);
    std::cout << glGetError() << std::endl;
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, dataSize, (void*)0);
    std::cout << glGetError() << std::endl;
    // Tex // Top Right // Bottom Right
    glEnableVertexAttribArray(1);
    std::cout << glGetError() << std::endl;
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, dataSize, (void*)(2 * sizeof(float)));
    std::cout << glGetError() << std::endl;
    // Tex // Bottom Left // Top Left
    glEnableVertexAttribArray(2);
    std::cout << glGetError() << std::endl;
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, dataSize, (void*)(6 * sizeof(float)));
    std::cout << glGetError() << std::endl;
    glBindVertexArray(0);
}

void TileManager::Draw()
{
    m_Shader->Use();
    glActiveTexture(GL_TEXTURE0);
    tileAtlas->Bind();

    m_Shader->SetMat4("projection", MainCamera->Projection);
    m_Shader->SetMat4("view", MainCamera->View);

    glBindVertexArray(VAO);
    std::cout << glGetError() << std::endl;
    glDrawArrays(GL_POINTS, 0, m_Tiles.size());
}

void TileManager::CreateTile(int tileId, glm::vec2 pos)
{
    m_Tiles.push_back(pos.x);
    m_Tiles.push_back(pos.y);

    for (int i = 0; i < 4; i++)
    {
        m_Tiles.push_back(m_TileSetCoords[tileId].Coords[i].x);
        m_Tiles.push_back(m_TileSetCoords[tileId].Coords[i].y);
    };



}


glm::mat4 TileManager::GetTransform(glm::vec2 pos)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.0f));

    model = glm::scale(model, glm::vec3(m_TileSize, m_TileSize, 1.0f));

    return model;
}


void TileManager::Destroy()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
}
