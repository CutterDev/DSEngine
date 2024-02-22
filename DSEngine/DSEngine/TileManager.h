#pragma 

#include "ResourceManager.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <string>

struct TileTexCoords {
    glm::vec2 TexCoords[4];
};

struct TileSetCoords {
    float Coords[8];
};

struct TilesToDraw{
    unsigned int VAO;
    unsigned int Amount;
    std::vector<glm::vec3> Offsets;
};

class TileManager
{
private:
    unsigned int VAO, VBO, EBO;
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
    
    std::vector<int> m_TileAtlasIds;
    std::map<int, TilesToDraw> m_Tiles;
    std::map<int, TileSetCoords> m_AtlasCoords;

    glm::mat4 GetTransform(glm::ivec2 pos);
    glm::mat4 Model;
public:

    TileManager(std::string texture, unsigned int tileSize, int tileSetSpacing = 0);
    void Initialize();
    void Draw(glm::mat4 projection, glm::mat4 view);
    void CreateTile(int tileId, glm::ivec2 pos);
    void Destroy();
};

