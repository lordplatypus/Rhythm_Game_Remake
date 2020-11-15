#include <SFML/Graphics.hpp>
#include <string>
#include "Game.h"
#include "MP.h"
#include "../Scene/SceneNull.h"
#include "../BPMScene/BPMScene.h"
#include "../TitleScene/TitleScene.h"

static SceneNull nullScene;

Game::Game(Camera* camera) : scene_{&nullScene}, camera_{camera}
{
    loadAssets_.Load();
    MP::ImportBPM();

    AddScene("Title", new TitleScene(this));
    AddScene("BPM", new BPMScene(this));

    scene_ = scenes_["Title"];
    scene_->Init();
}

Game::~Game()
{
    Clear();
}

void Game::Update(float delta_time, float beat_time)
{
    scene_->Update(delta_time, beat_time);
}

void Game::Draw()
{
    scene_->Draw();
}

void Game::AddScene(const std::string& name, Scene* scene)
{
    scenes_[name] = scene;
}

void Game::ChangeScene(const std::string& newScene)
{
    EndScene();
    scene_ = scenes_[newScene];
    scene_->Init();
}

void Game::EndScene()
{
    scene_->End();
    scene_ = &nullScene;
}

Camera* Game::GetCamera()
{
    return camera_;
}

void Game::Clear()
{
    scene_->End();

    for (auto pair : scenes_)
    {
        delete pair.second;
    }
    scenes_.clear();
}