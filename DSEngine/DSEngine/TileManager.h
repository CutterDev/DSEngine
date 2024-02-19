#pragma 
#include "ResourceManager.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <string>

struct Tile {
    glm::vec2 Position;
    glm::vec2 TexCoords[4];
};

struct TileCoords {
    glm::vec2 Coords[4];
};

class TileManager
{
private:
    unsigned int VAO, VBO, EBO;
    Shader* m_Shader;
    Texture2D tileAtlas;
    // Tiles To be drawn
    std::vector<float> m_Tiles;
    unsigned int m_TileSize;
    unsigned int m_TileSpacing;

    // How big the tile is on the atlas with spacing;
    unsigned int m_AtlasTileSize;
    // How many Tiles in a row
    unsigned int m_AtlasTilesX;
    unsigned int m_AtlasTilesY;

    TileCoords m_TileSetCoords[];

    glm::mat4 GetTransform(glm::vec2 pos);
public:

    TileManager(std::string texture, unsigned int tileSize, int tileSetSpacing = 0);
    void Initialize();
    void Draw(glm::mat4 projection, glm::mat4 view);
    void CreateTile(int tileId, glm::vec2 pos);
    void Destroy();
};

