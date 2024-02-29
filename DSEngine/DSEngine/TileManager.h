#pragma 

#include "ResourceManager.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include "glm/gtx/hash.hpp"
#include <map>
#include <memory>
#include <string>

struct TileAtlas{
    unsigned int VAO;
    unsigned int TexCoordsBuffer;
    unsigned int PositionsBuffer;
    unsigned int Amount;
    float TextureCoords[8];
    std::vector<glm::ivec2> Offsets;

    void Init() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &TexCoordsBuffer);
        glGenBuffers(1, &PositionsBuffer);

        // Todo Allocation of tiles needs to be correctly addressed.
        Offsets.resize(1000, glm::ivec2(0, 0));
    }

    void Update() {
        if (Amount > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, PositionsBuffer);

            void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

            memcpy(ptr, &Offsets[0], Offsets.size() * sizeof(glm::vec2));
            // make sure to tell OpenGL we're done with the pointer
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }
    }
    
    void Draw() {
        if (Amount > 0)
        {
            glBindVertexArray(VAO);
            glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, Amount);
        }
    }

    void Destroy()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &TexCoordsBuffer);
        glDeleteBuffers(1, &PositionsBuffer);
    }
};

struct TileIndex {
    unsigned int TileId;
};

class TileManager
{
private:
    unsigned int VBO, EBO;
    Shader* m_Shader;
    Texture2D tileAtlas;
    unsigned int m_TilesAmount;

    unsigned int m_TileSize;
    unsigned int m_TileSpacing;

    // How big the tile is on the atlas with spacing;
    unsigned int m_AtlasTileSize;
    // How many Tiles in a row
    unsigned int m_AtlasTilesX;
    unsigned int m_AtlasTilesY;

    bool m_IsAlive;

    std::vector<int> m_TileAtlasIds;
    std::map<int, TileAtlas> m_Tiles;
    std::vector<int> m_ActiveTiles;
    // Tile Positions on the Map Tile Id
    std::unordered_map <glm::ivec2, TileIndex> m_TileIndex;
public:

    TileManager() {};
    TileManager(std::string texture, unsigned int tileSize, int tileSetSpacing = 0);
    void Initialize();
    void Draw(glm::mat4 projection, glm::mat4 view);
    void CreateTile(int tileId, glm::ivec2 pos);
    void ClearTile(glm::vec2 worldPos);
    void SetTile(int tileId, glm::ivec2 pos);
    void Destroy();

    glm::ivec2 GetTileFromWorldPos(glm::vec2 worldPos);
};

