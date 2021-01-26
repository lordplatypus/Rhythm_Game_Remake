#ifndef TILEMAP_H_
#define TILEMAP_H_
#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool Load(const sf::Texture& tilesetTexture, sf::Vector2u tileSize, const std::vector<std::vector<int>> map, sf::Vector2f position, int width, int height);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::VertexArray vertices_;
    sf::Texture texture_;
};

#endif