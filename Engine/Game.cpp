#include <SFML/Graphics.hpp>
#include <string>
#include "Game.h"
#include "MP.h"
#include "IP.h"
#include "../Scene/SceneNull.h"
#include "../BPMScene/BPMScene.h"
#include "../MusicSelect/MusicSelect.h"
#include "../TitleScene/TitleScene.h"
#include "../LobbyScene/LobbyScene.h"
#include "../TestScene/TestScene.h"
#include "../StartingItemScene/StartingItemScene.h"
#include "../JunkYardScene/JunkYardScene.h"
#include "../Stage1/Stage1_1.h"
#include "../Stage1/Stage1_2.h"
#include "../Stage1/Stage1_3.h"

static SceneNull nullScene;

Game::Game(Camera* camera) : scene_{&nullScene}, camera_{camera}
{
    loadAssets_.Load();
    MP::ImportBPM();
    playerManager_ = new PlayerManager(camera_);

    AddScene("Title", new TitleScene(this));
    AddScene("Lobby", new LobbyScene(this));
    AddScene("BPM", new BPMScene(this));
    AddScene("MusicSelect", new MusicSelect(this));
    AddScene("Test", new TestScene(this));
    AddScene("Item", new StartingItemScene(this));
    AddScene("JunkYard", new JunkYardScene(this));
    AddScene("Stage1_1", new Stage1_1(this));
    AddScene("Stage1_2", new Stage1_2(this));
    AddScene("Stage1_3", new Stage1_3(this));

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
    IP::Reset();
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

PlayerManager* Game::GetPlayerManager()
{
    return playerManager_;
}

GlobalEnemyManager* Game::GetGlobalEnemyManager()
{
    return &gem_;
}

TransitionManager* Game::GetTransitionManager()
{
    return &transitionManager_;
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