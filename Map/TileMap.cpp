#include "TileMap.h"

bool TileMap::Load(const sf::Texture& tilesetTexture, sf::Vector2u tileSize, const std::vector<std::vector<int>> map, sf::Vector2f position, int width, int height)
{
    texture_ = tilesetTexture;

    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(width * height * 4);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            //int tileNumber = map[x + y * width];
            int tileNumber = map[x][y];
            if (tileNumber == -1) continue;

            int tu = tileNumber % (texture_.getSize().x / tileSize.x);
            int tv = tileNumber / (texture_.getSize().x / tileSize.x);

            sf::Vertex* quad = &vertices_[(x + y * width) * 4];

            quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
            quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
            quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    setPosition(position);

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = &texture_;

    target.draw(vertices_, states);
}