#include "LP.h"
#include "../Assets/Assets.h"

std::unordered_map<int, sf::Texture> LP::textureMap_;
sf::Font LP::font_;

//SPRITE
void LP::SetTexture(const int textureKey, const std::string& filePath, int width, int height)
{
    textureMap_[textureKey].loadFromFile(filePath, sf::IntRect(0, 0, width, height));
}

sf::Sprite LP::SetSprite(const int textureKey, const sf::Vector2f& position)
{
    sf::Sprite temp;
    temp.setTexture(textureMap_[textureKey]);
    temp.setPosition(position);
    return temp;
}

sf::Sprite LP::SetSprite(const int textureKey, const int cellWidth, const int cellHeight, const int cellID, const sf::Vector2f& position)
{
    sf::Sprite temp;
    temp.setTexture(textureMap_[textureKey]);
    sf::Vector2u textureSize = temp.getTexture()->getSize();
    temp.setTextureRect(sf::IntRect(cellID % (textureSize.x / cellWidth) * cellWidth, cellID / (textureSize.x / cellWidth) * cellWidth, cellWidth, cellHeight));
    temp.setPosition(position);
    return temp;
}

std::vector<sf::Sprite> LP::SetMultiFrameSprite(const int textureKey, const int cellWidth, const int cellHeight, const int numOfColumns, const int numOfRows, const sf::Vector2f& position)
{
    std::vector<sf::Sprite> spriteArray;
    for (int i = 0; i < numOfRows; i++)
    {
        for (int j = 0; j < numOfColumns; j++)
        {
            sf::Sprite temp;
            temp.setTexture(textureMap_[textureKey]);
            temp.setTextureRect(sf::IntRect(cellWidth * j, cellHeight * i, cellWidth, cellHeight));
            temp.setPosition(position);
            spriteArray.push_back(temp);
        }
    }
    return spriteArray;
}

void LP::SetSpriteHorizontalFlip(sf::Sprite* sprite, const bool flip)
{
    if (flip && sprite->getScale().x > 0)
    {
        sprite->scale(-1.0f, 1.0f);
        sprite->setOrigin(sprite->getLocalBounds().width, sprite->getOrigin().y);
    }
    else if (!flip && sprite->getScale().x < 0)
    {
        sprite->scale(-1.0f, 1.0f);
        sprite->setOrigin(0, sprite->getOrigin().y);
    }
}

void LP::SetSpriteOriginCenter(sf::Sprite* sprite)
{
    sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);
}


//TEXT
void LP::SetFont(const std::string& filePath)
{
    font_.loadFromFile(filePath);
}

sf::Text LP::SetText(const std::string& string, const sf::Vector2f& position, const int textSize, const sf::Vector2f& scale)
{
    sf::Text text;
    text.setFont(font_);
    text.setCharacterSize(textSize);
    text.setPosition(position);
    text.setFillColor(sf::Color::White);
    text.setString(string);
    text.setScale(scale);
    return text;
}

void LP::SetTextOriginCenter(sf::Text* text)
{
    text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
}


//TILEMAP
TileMap LP::SetTileMap(const int textureKey, sf::Vector2u tileSize, const int* map, sf::Vector2f position, int width, int height)
{
    TileMap temp;
    temp.Load(textureMap_[textureKey], tileSize, map, position, width, height);
    return temp;
}