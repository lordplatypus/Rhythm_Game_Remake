#include "LP.h"

int LP::key = 0; //creates keys to use in the below maps
std::queue<int> LP::thingsToDraw; //list of ints (keys) used to know what to draw
std::unordered_map<int, sf::RectangleShape> LP::rectangleMap; //map of rectangles
std::unordered_map<int, sf::CircleShape> LP::circleMap; //map of circles
std::unordered_map<int, sf::Texture> LP::textureMap;
std::unordered_map<int, sf::Sprite> LP::spriteMap;
sf::Font LP::font;
std::unordered_map<int, sf::Text> LP::textMap;

LP::LP(){}

LP::~LP(){}

int LP::SetCircle(const sf::Vector2f position, const float radius)
{
    key++;
    circleMap[key].setPosition(position);
    circleMap[key].setRadius(radius);
    circleMap[key].setFillColor(sf::Color::White);
    return key;
}

void LP::DrawCircle(const int key)
{
    thingsToDraw.push(key);
}

void LP::DrawCircle(const int key, const sf::Vector2f position)
{
    circleMap[key].setPosition(position);
    thingsToDraw.push(key);
}

void LP::SetCircleColor(const int key, const int red, const int green, const int blue, const int alpha)
{
    circleMap[key].setFillColor(sf::Color(red, green, blue, alpha));
}

void LP::SetCircleRadius(const int key, const float radius)
{
    circleMap[key].setRadius(radius);
}


//Drawing Rectangles
int LP::SetRectangle(const sf::Vector2f position, const float width, const float height)
{
    key++;
    rectangleMap[key].setPosition(position);
    rectangleMap[key].setSize(sf::Vector2f(width, height));
    rectangleMap[key].setFillColor(sf::Color::White);
    return key;
}

void LP::DrawRectangle(const int key)
{
    thingsToDraw.push(key);
}

void LP::DrawRectangle(const int key, const sf::Vector2f position)
{
    rectangleMap[key].setPosition(position);
    thingsToDraw.push(key);
}

void LP::SetRectangleColor(const int key, const int red, const int green, const int blue, const int alpha)
{
    rectangleMap[key].setFillColor(sf::Color(red, green, blue, alpha));
}

void LP::SetRectangleSize(const int key, const float width, const float height)
{
    rectangleMap[key].setSize(sf::Vector2f(width, height));
}

//Drawing sprites
int LP::SetTexture(const std::string& filePath, int width, int height)
{
    key++;
    textureMap[key].loadFromFile(filePath, sf::IntRect(0, 0, width, height));
    return key;
}

void LP::SetTexture(const int key, const std::string& filePath, int width, int height)
{
    textureMap[key].loadFromFile(filePath, sf::IntRect(0, 0, width, height));
}

int LP::SetSprite(const int textureKey)
{
    key++;
    spriteMap[key].setTexture(textureMap[textureKey]);
    return key;
}

int LP::SetSprite(const int textureKey, const sf::Vector2f position)
{
    key++;
    spriteMap[key].setTexture(textureMap[textureKey]);
    spriteMap[key].setPosition(position);
    return key;
}

int LP::SetSprite(const int textureKey, const sf::Vector2f position, const int cellWidth, const int cellHeight, const int cellID)
{
    key++;
    spriteMap[key].setTexture(textureMap[textureKey]);
    sf::Vector2u textureSize = textureMap[textureKey].getSize();
    spriteMap[key].setTextureRect(sf::IntRect(cellID % (textureSize.x / cellWidth) * cellWidth, cellID / (textureSize.x / cellWidth) * cellWidth, cellWidth, cellHeight));
    spriteMap[key].setPosition(position);
    return key;
}

std::vector<int> LP::SetSprite(const int textureKey, const int cellWidth, const int cellHeight, const int numOfColumns, const int numOfRows)
{
    std::vector<int> spriteArray;
    for (int i = 0; i < numOfRows; i++)
    {
        for (int j = 0; j < numOfColumns; j++)
        {
            key++;
            spriteMap[key].setTexture(textureMap[textureKey]);
            spriteMap[key].setTextureRect(sf::IntRect(cellWidth * j, cellHeight * i, cellWidth, cellHeight));
            spriteArray.push_back(key);
        }
    }
    return spriteArray;
}

void LP::DrawSprite(const int key)
{
    thingsToDraw.push(key);
}

void LP::DrawSprite(const int key, sf::Vector2f position)
{
    spriteMap[key].setPosition(position);
    thingsToDraw.push(key);
}

void LP::SetSpriteColor(const int key, const int red, const int green, const int blue, const int alpha)
{
    spriteMap[key].setColor(sf::Color(red, green, blue, alpha));
}

void LP::SetSpritePosition(const int key, const sf::Vector2f position)
{
    spriteMap[key].setPosition(position);
}

void LP::SetSpriteRotation(const int key, const float angle)
{
    spriteMap[key].setRotation(angle);
}

void LP::SetSpriteOrigin(const int key, const sf::Vector2f newOrigin)
{
    spriteMap[key].setOrigin(newOrigin);
}

void LP::SetSpriteOriginCenter(const int key)
{
    spriteMap[key].setOrigin(spriteMap[key].getLocalBounds().width / 2, spriteMap[key].getLocalBounds().height / 2);
}

void LP::SetSpriteScale(const int key, const float scaleX, const float scaleY)
{
    spriteMap[key].setScale(scaleX, scaleY);
}

void LP::SetSpriteHorizontalFlip(const int key, const bool flip)
{
    if (flip && spriteMap[key].getScale().x > 0)
    {
        spriteMap[key].scale(-1.0f, 1.0f);
        spriteMap[key].setOrigin(spriteMap[key].getLocalBounds().width, spriteMap[key].getOrigin().y);
    }
    else if (!flip && spriteMap[key].getScale().x < 0)
    {
        spriteMap[key].scale(-1.0f, 1.0f);
        spriteMap[key].setOrigin(0, spriteMap[key].getOrigin().y);
    }
}


//Drawing Text
void LP::SetFont(const std::string& filePath)
{
    font.loadFromFile(filePath);
}

int LP::SetText(const std::string& text, const sf::Vector2f position, int textSize)
{
    key++;
    textMap[key].setFont(font);
    textMap[key].setCharacterSize(textSize);
    textMap[key].setPosition(position);
    textMap[key].setFillColor(sf::Color::White);
    textMap[key].setString(text);
    return key;
}

void LP::SetTextString(const int key, const std::string& text)
{
    textMap[key].setString(text);
}

int LP::DuplicateText(const int keyToDup)
{
    key++;
    textMap[key].setFont(font);
    textMap[key].setCharacterSize(textMap[keyToDup].getCharacterSize());
    textMap[key].setPosition(textMap[keyToDup].getPosition());
    textMap[key].setFillColor(textMap[keyToDup].getFillColor());
    textMap[key].setString(textMap[keyToDup].getString());
    return key;
}

void LP::SetTextColor(const int key, const sf::Color color)
{
    textMap[key].setFillColor(color);
}

void LP::SetTextColor(const int key, const int red, const int green, const int blue, const int alpha)
{
    textMap[key].setFillColor(sf::Color(red, green, blue, alpha));
}

void LP::SetTextOrigin(const int key, const sf::Vector2f newOrigin)
{
    textMap[key].setOrigin(newOrigin);
}

void LP::SetTextOriginCenter(const int key)
{
    textMap[key].setOrigin(textMap[key].getLocalBounds().width / 2, textMap[key].getLocalBounds().height / 2);
}

void LP::SetTextPosition(const int key, const sf::Vector2f newPosition)
{
    textMap[key].setPosition(newPosition);
}

void LP::SetTextScale(const int key, const float scaleX, const float scaleY)
{
    textMap[key].setScale(scaleX, scaleY);
}

void LP::DrawText(int key)
{
    thingsToDraw.push(key);
}

void LP::DrawText(const int key, const std::string& text)
{
    textMap[key].setString(text);
    thingsToDraw.push(key);
}


//Draw
void LP::Draw(sf::RenderWindow *window)
{
    if(thingsToDraw.size() > 0)
    {//as long as there are things to draw, run the below code
        int numOfThingsToDraw = thingsToDraw.size(); //save the num of things to draw
        for (int i = 0; i < numOfThingsToDraw; i++)
        {
            if (circleMap.find(thingsToDraw.front()) != circleMap.end())
            {//if the circleMap contains the key draw the circle
                window->draw(circleMap[thingsToDraw.front()]);
            }
            else if (rectangleMap.find(thingsToDraw.front()) != rectangleMap.end())
            {//if the rectangleMap contains the key, draw the rectangle
                window->draw(rectangleMap[thingsToDraw.front()]);
            }
            else if (spriteMap.find(thingsToDraw.front()) != spriteMap.end())
            {
                window->draw(spriteMap[thingsToDraw.front()]);
            }
            else if (textMap.find(thingsToDraw.front()) != textMap.end())
            {
                window->draw(textMap[thingsToDraw.front()]);
            }
            thingsToDraw.pop(); //remove the key from the list
        }
    }
}


//Delete
void LP::DeleteCircle(int key)
{
    circleMap.erase(key);
}

void LP::DeleteRectangle(int key)
{
    rectangleMap.erase(key);
}

void LP::DeleteTexture(int key)
{
    textureMap.erase(key);
}

void LP::DeleteSprite(int key)
{
    spriteMap.erase(key);
}

void LP::DeleteText(int key)
{
    textMap.erase(key);
}

void LP::DeleteAll()
{
    circleMap.clear();
    rectangleMap.clear();
}