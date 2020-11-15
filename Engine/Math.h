#ifndef MATH_H_
#define MATH_H_
#include <SFML/Graphics.hpp>
#include <cmath>

class Math
{
public:
    static sf::Vector2f Lerp(sf::Vector2f v0, sf::Vector2f v1, float t) 
    {
        return (1 - t) * v0 + t * v1;
    }
    static float Lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    } 
    static float PI()
    {
        return M_PI;
    }
    static float RoundUp(float a)
    {
        return ceil(a);
    }
};

#endif