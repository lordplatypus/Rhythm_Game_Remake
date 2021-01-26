#ifndef ASSETS_H_
#define ASSETS_H_
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Assets
{
public:
    Assets();
    ~Assets();
    void Load();

private:
    void LoadImage();
    void LoadSound();
    void LoadStageMusic();
};

#endif