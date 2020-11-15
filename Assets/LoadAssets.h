#ifndef LOAD_ASSETS_H_
#define LOAD_ASSETS_H_

class LoadAssets
{
public:
    LoadAssets();
    ~LoadAssets();
    void Load();

private:
    void LoadImage();
    void LoadSound();
};

#endif