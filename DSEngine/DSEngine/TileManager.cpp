#include "TileManager.h"
#include "LightComponent.h"
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

void TileManager::Startup(std::string texture, unsigned int tileSize, int tileSetSpacing, int resolution)
{
    m_Shader.Startup("tile.vs", "tile.fs");
    m_TileSize = tileSize;
    m_TileSpacing = tileSetSpacing;
    m_AtlasTileSize = tileSize + tileSetSpacing;
    m_Resolution = resolution;
    m_Shader.Use();
    m_Shader.SetInt("ourTexture", 0);
    m_Shader.SetFloat("tileSize", m_TileSize * resolution);
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

    int tileid = 0;

   
    for (int y = 0; y < m_AtlasTilesY; y++)
    {
        for (int x = 0; x < m_AtlasTilesX; x++)
        {
            m_Tiles[tileid] = {};
            m_Tiles[tileid].Init();

            // Top Right
            m_Tiles[tileid].TextureCoords[0] = (float)(m_AtlasTileSize + (m_AtlasTileSize * x)) / width;
            m_Tiles[tileid].TextureCoords[1] = ((float)(tileSetSpacing + (m_AtlasTileSize * y)) / height);
            // Bottom Right
            m_Tiles[tileid].TextureCoords[2] = (float)(m_AtlasTileSize + (m_AtlasTileSize * x)) / width;
            m_Tiles[tileid].TextureCoords[3] = ((float)(m_AtlasTileSize + (m_AtlasTileSize * y)) / height);

            // Bottom Left
            m_Tiles[tileid].TextureCoords[4] = (float)(tileSetSpacing + (m_AtlasTileSize * x)) / width;
            m_Tiles[tileid].TextureCoords[5] = ((float)(m_AtlasTileSize + (m_AtlasTileSize * y)) / height);
                // Top Left
            m_Tiles[tileid].TextureCoords[6] = (float)(tileSetSpacing + (m_AtlasTileSize * x)) / width;
            m_Tiles[tileid].TextureCoords[7] = ((float)(tileSetSpacing + (m_AtlasTileSize * y)) / height);

            tileid++;
        }
    }
}

void TileManager::Populate()
{
    float vertices[] = {
        // positions          // colors        
     1.0f,  0.0f, 0.f,   1.0f, 1.0f, 1.0f,   // top right
     1.0f, 1.0f, 0.f,   1.0f, 1.0f, 1.0f,   // bottom right
     0.0f, 1.0f, 0.f,   1.0f, 1.0f, 1.0f,   // bottom left
     0.0f,  0.0f, 0.f,   1.0f, 1.0f, 1.0f  // top left 
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

    for (int i = 0; i < m_Tiles.size(); i++)
    {
        int tileid = i;
        glBindVertexArray(m_Tiles[tileid].VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Vertex attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture Buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_Tiles[tileid].TexCoordsBuffer);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), &m_Tiles[tileid].TextureCoords[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_Tiles[tileid].PositionsBuffer);

        // Positions Attribute
        glEnableVertexAttribArray(3);
        glVertexAttribIPointer(3, 2, GL_INT, 2 * sizeof(GLint), (void*)0);
        glVertexAttribDivisor(3, 1);

        glBufferData(GL_ARRAY_BUFFER, m_Tiles[tileid].Offsets.size() * sizeof(glm::ivec2), &m_Tiles[tileid].Offsets[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
    }
    m_IsAlive = true;
}

void TileManager::Draw(glm::mat4 projection, glm::mat4 view, std::vector<Light> lights)
{
    glActiveTexture(GL_TEXTURE0);

    tileAtlas.Bind();

    m_Shader.Use();
    
    glm::vec4 lightPos = projection * (view * glm::vec4(lights[0].LightPos, 1.0f, 1.0f));
    glm::vec3 ndsPos = glm::vec3(lightPos) / lightPos.w;

    
    m_Shader.SetMat4("projection", projection);
    m_Shader.SetMat4("view", view);
    m_Shader.SetVec2("aPos", lights[0].LightPos);
    m_Shader.SetVec4("aAmbiance", glm::vec4(1.f, 1.f, 1.f, 0.3f));
    m_Shader.SetVec4("aLightColor", lights[0].LightColor);
    m_Shader.SetFloat("aDistance", lights[0].Distance);

    // TODO: Only go through an active list of tile ids. to save some memory
    for (int i = 0; i < m_Tiles.size(); i++)
    {
        m_Tiles[i].Draw();
    }
}

void TileManager::SetTile(int tileId, glm::ivec2 pos, b2World* world)
{
    bool instanceExists = m_TileIndex.find(pos) != m_TileIndex.end();

    bool tileIdMatches = false;

    if (instanceExists && m_TileIndex[pos].TileId != -1)
    {
        tileIdMatches = tileId == m_TileIndex[pos].TileId;

        if (!tileIdMatches)
        {
            int currentId = m_TileIndex[pos].TileId;

            // Remove from Instances
            // Find tile from actual x/y position by posX % TileSize
            std::vector<glm::ivec2>::iterator position = std::find(m_Tiles[currentId].Offsets.begin(), m_Tiles[currentId].Offsets.end(), pos);
            if (position != m_Tiles[currentId].Offsets.end()) // == myVector.end() means the element was not found
            {
                m_Tiles[currentId].Offsets.erase(position);
                m_Tiles[currentId].Offsets.push_back(glm::ivec2(0.f, 0.f));
                m_Tiles[currentId].Amount--;
                m_TileIndex[pos].TileId = -1;
            }

            if (m_IsAlive)
            {
                m_Tiles[currentId].Update();
            }
        }
    }

    if (!tileIdMatches && tileId != -1)
    {
        bool reallocateMemory = false;
        if (m_Tiles[tileId].Offsets.size() > m_Tiles[tileId].Amount)
        {
            std::vector<glm::ivec2>::iterator position = m_Tiles[tileId].Offsets.begin() + (m_Tiles[tileId].Amount);
            *position = pos;
        }
        else
        {
            m_Tiles[tileId].Offsets.push_back(pos);
            reallocateMemory = true;
        }
            

        m_Tiles[tileId].Amount++;
        m_TileIndex[pos].TileId = tileId;

        if (m_IsAlive)
        {
            if (reallocateMemory)
            {
                m_Tiles[tileId].AllocatePositionsMemory();
            }
            else {
                m_Tiles[tileId].Update();
            }

        }

        if (m_TileIndex[pos].TileId == -1)
        {
            // delete collider
        }
        else {
            // Create collider
            
            b2BodyDef groundBodyDef;
            groundBodyDef.position.Set(pos.x * (m_TileSize * m_Resolution), pos.y * (m_TileSize * m_Resolution));

            m_Colliders[pos] = world->CreateBody(&groundBodyDef);

            ////float boxSize = (m_TileSize * m_Resolution) * 0.02f;
            ////b2PolygonShape groundBox;
            ////groundBox.SetAsBox(boxSize, boxSize);

            //m_Colliders[pos]->CreateFixture(&groundBox, 0.0f);
        }
    }
}

glm::ivec2 TileManager::GetTileFromWorldPos(glm::vec2 worldPos)
{
    glm::ivec2 tilePos = glm::ivec2((int)(worldPos.x / (m_TileSize * m_Resolution)), (int)(worldPos.y / (m_TileSize * m_Resolution)));


    if (worldPos.x < 0)
    {
        tilePos.x--;
    }

    if (worldPos.y < 0)
    {
        tilePos.y--;
    }
    return tilePos;
}


void TileManager::Destroy()
{
    for (int i = 0; i < m_Tiles.size(); i++)
    {
        m_Tiles[i].Destroy();
    }

    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);

    m_Shader.Delete();
}
