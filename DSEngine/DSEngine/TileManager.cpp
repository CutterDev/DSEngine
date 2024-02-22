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

    m_Shader = new Shader("sprite.vs", "sprite.fs");
    m_Shader->Use();
    m_Shader->SetInt("ourTexture", 0);
    m_Shader->SetFloat("tileSize", m_TileSize);
    // Create new Texture was not found.
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texture.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        tileAtlas.Internal_Format = GL_RGBA;
        tileAtlas.Image_Format = GL_RGBA;

        // now generate texture
        tileAtlas.Generate(width, height, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // and finally free image data
    stbi_image_free(data);

    m_AtlasTilesX = tileAtlas.Width / (tileSize + tileSetSpacing);
    m_AtlasTilesY = tileAtlas.Height / (tileSize + tileSetSpacing);

    int totalTile = m_AtlasTilesX * m_AtlasTilesY;

    int tileId = 0;

   
    for (int y = 0; y < m_AtlasTilesY; y++)
    {
        for (int x = 0; x < m_AtlasTilesX; x++)
        {
            // Top Right
            m_AtlasCoords[tileId].Coords[0] = (float)(m_AtlasTileSize + (m_AtlasTileSize * x)) / width;
            m_AtlasCoords[tileId].Coords[1] = 1.f - ((float)(tileSetSpacing + (m_AtlasTileSize * y)) / height);
            // Bottom Right
            m_AtlasCoords[tileId].Coords[2] = (float)(m_AtlasTileSize + (m_AtlasTileSize * x)) / width;
            m_AtlasCoords[tileId].Coords[3] = 1.f - ((float)(m_AtlasTileSize + (m_AtlasTileSize * y)) / height);

            // Bottom Left
            m_AtlasCoords[tileId].Coords[4] = (float)(tileSetSpacing + (m_AtlasTileSize * x)) / width;
            m_AtlasCoords[tileId].Coords[5] = 1.f - ((float)(m_AtlasTileSize + (m_AtlasTileSize * y)) / height);
                // Top Left
            m_AtlasCoords[tileId].Coords[6] = (float)(tileSetSpacing + (m_AtlasTileSize * x)) / width;
            m_AtlasCoords[tileId].Coords[7] = 1.f - ((float)(tileSetSpacing + (m_AtlasTileSize * y)) / height);

            tileId++;
        }
    }

    Model = glm::mat4(1.0f);
    Model = glm::translate(Model, glm::vec3(0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    Model = glm::scale(Model, glm::vec3(m_TileSize, m_TileSize, 1.0f)); // last scale
}

void TileManager::Initialize()
{
   
    float vertices[] = {
        // positions          // colors        
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };


    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    for (int i = 0; i < m_TileAtlasIds.size(); i++)
    {
        int tileid = m_TileAtlasIds[i];
        glBindVertexArray(m_Tiles[tileid].VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        unsigned int texCoordBuffer;
        glGenBuffers(1, &texCoordBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), &m_AtlasCoords[tileid].Coords[0], GL_STATIC_DRAW);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);

        // vertex buffer object
        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, m_Tiles[tileid].Amount * sizeof(glm::vec3), &m_Tiles[tileid].Offsets[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        glVertexAttribDivisor(3, 1);

        glBindVertexArray(0);
    }
}

void TileManager::Draw(glm::mat4 projection, glm::mat4 view)
{
    glActiveTexture(GL_TEXTURE0);

    tileAtlas.Bind();

    m_Shader->Use();


    m_Shader->SetMat4("projection", projection);

    m_Shader->SetMat4("view", view);
    m_Shader->SetMat4("model", Model);

    for (int i = 0; i < m_TileAtlasIds.size(); i++)
    {
        int tileId = m_TileAtlasIds[i];
        glBindVertexArray(m_Tiles[tileId].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_Tiles[tileId].Amount);
    }
}

void TileManager::CreateTile(int tileId, glm::ivec2 pos)
{
    glm::vec3 gridPos = glm::vec3((glm::vec2)pos * (float)m_TileSize, 0.0f);
    if (m_Tiles.find(tileId) == m_Tiles.end())
    {
        m_TileAtlasIds.push_back(tileId);

        TilesToDraw tile = TilesToDraw{};
        glGenVertexArrays(1, &tile.VAO);
        tile.Offsets.push_back(gridPos);
        tile.Amount = 1;
        m_Tiles[tileId] = tile;
    }
    else {
        m_Tiles[tileId].Offsets.push_back(gridPos);
        m_Tiles[tileId].Amount++;
    }
}


void TileManager::Destroy()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);

    m_Shader->Delete();
}
