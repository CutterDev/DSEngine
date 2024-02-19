#include "TileManager.h"
GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

TileManager::TileManager(std::string texture, unsigned int tileSize, int tileSetSpacing)
{
    m_TileSize = tileSize;
    m_TileSpacing = tileSetSpacing;
    m_AtlasTileSize = tileSize + tileSetSpacing;

    m_Shader = new Shader("tile.vs", "tile.fs", "tile.gs");

    tileAtlas = ResourceManager::GetInstance().GetTexture(texture, true);
    m_AtlasTilesX = tileAtlas->Width / (tileSize + tileSetSpacing);
    m_AtlasTilesY = tileAtlas->Height / (tileSize + tileSetSpacing);


    m_TileSetCoords[m_AtlasTilesX * m_AtlasTilesY];

    int tileId = 0;

    float width = tileAtlas->Width;
    float height = tileAtlas->Height;

    for (int y = 0; y < m_AtlasTilesY; y++)
    {
        for (int x = 0; x < m_AtlasTilesX; x++)
        {
            m_TileSetCoords[tileId] = TileCoords{
                // Top Right
                glm::vec2((float)(m_AtlasTileSize + (m_AtlasTileSize * x)) / width,
                (float)(tileSetSpacing +(m_AtlasTileSize * y))) / height,
                // Bottom Right
                glm::vec2((float)(m_AtlasTileSize + (m_AtlasTileSize * x)) / width,
                (float)(m_AtlasTileSize + (m_AtlasTileSize * y))) / height,
                // Bottom Left
                glm::vec2((float)(tileSetSpacing + (m_AtlasTileSize * x)) / width,
                (float)(m_AtlasTileSize + (m_AtlasTileSize * y))) / height,

                // Top Left
                glm::vec2((float)(tileSetSpacing + (m_AtlasTileSize * x)) / width,
                (float)(tileSetSpacing + (m_AtlasTileSize * y))) / height
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
    glCheckError();
    // Tex // Top Right // Bottom Right
    glEnableVertexAttribArray(0);
    glCheckError();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, dataSize, (void*)0);
    glCheckError();
    // Tex // Top Right // Bottom Right
    glEnableVertexAttribArray(1);
    glCheckError();
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, dataSize, (void*)(2 * sizeof(float)));
    glCheckError();
    // Tex // Bottom Left // Top Left
    glEnableVertexAttribArray(2);
    glCheckError();
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, dataSize, (void*)(6 * sizeof(float)));
    glCheckError();
    glBindVertexArray(0);
}

void TileManager::Draw(glm::mat4 projection, glm::mat4 view)
{
    m_Shader->Use();
    glCheckError();
    glActiveTexture(GL_TEXTURE0);
    glCheckError();
    tileAtlas->Bind();
    glCheckError();
    m_Shader->SetMat4("projection", projection);
    glCheckError();
    m_Shader->SetMat4("view", view);
    glCheckError();
    glBindVertexArray(VAO);

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

    m_Shader->Delete();
}
