#include "TutorialScene.h"
#include "TutorialMap.h"
#include "../Assets/ID.h"
#include "../Engine/IP.h"
#include "../Engine/MP.h"
#include "../Engine/Math.h"
#include "TutorialTextObject.h"
#include "../Event/FindKeys.h"

TutorialScene::TutorialScene(Game* game) : game_{game}
{}

TutorialScene::~TutorialScene()
{}

void TutorialScene::Init()
{
    game_->GetTransitionManager()->SetCurrentScene("Tutorial");
    lem_ = new LocalEnemyManager(game_->GetGlobalEnemyManager());
    map_ = new TutorialMap(this, game_->GetCamera(), game_->GetPlayerManager(), lem_, game_->GetGlobalEnemyManager(), game_->GetTransitionManager(), &pm_);
    game_->GetCamera()->SetCameraViewSize(360.f, 240.f);
    game_->GetCamera()->SetTarget(gameObjects_.Find("Player")->GetPosition());
    pm_.FadeFromBlack(gameObjects_.Find("Player")->GetPosition().x, gameObjects_.Find("Player")->GetPosition().y);
    MP::PlayStageMusic(tutorial, true);
    transitionTo_ = "";

    AddGameObject(new TutorialTextObject(sf::Vector2f(3*32, 4*32), "All actions must be done on beat\n\nUse the arrow keys to move the character\n\nUse the WASD to attack", this));
    AddGameObject(new TutorialTextObject(sf::Vector2f(10*32, 4*32), "Match the arrows above the enemy with the right attack to damage it\n\nLeft: A   Right: D   Up: W   Down: S\n\nComplete the sequence from left to right to defeat the enemy", this));
    AddGameObject(new TutorialTextObject(sf::Vector2f(17*32, 4*32), "Enemies have a certain pattern that they will follow\n\n(Most) Enemies will have their eye turn red before moving\n\nIf an enemy moves onto the same tile as the player,\n\nthe player will take damage", this));
    AddGameObject(new TutorialTextObject(sf::Vector2f(24*32, 4*32), "Stairs will lead to the next stage\n\nEvents(show in the top left) must be cleared to unlock the stairs\n\nin this case, pick up the key by being at least 1 tile away\n\nand by pressing the correct attack", this));

    AddGameObject(new FindKeys("Lobby", game_->GetCamera(), game_->GetTransitionManager(), game_->GetPlayerManager(), this, &pm_, map_, true, sf::Vector2f(24*32, 5*32)));
}

void TutorialScene::Update(float delta_time, float beat_time)
{
    gameObjects_.Update(delta_time, beat_time);
    gameObjects_.Collision();
    gameObjects_.Perception();
    gameObjects_.Remove();
    pm_.Update(delta_time);

    game_->GetCamera()->SetTarget(Math::Lerp(game_->GetCamera()->GetCameraCenter(), gameObjects_.Find("Player")->GetPosition() + sf::Vector2f(8, 8), 10 * delta_time));

    if (transitionTo_ != "") 
    {
        game_->ChangeScene(transitionTo_);
        game_->GetPlayerManager()->Init();
        game_->GetGlobalEnemyManager()->Clear();
    }

    if (IP::PressX())
    {//Return to TitleScene
        game_->ChangeScene("Lobby");
        game_->GetPlayerManager()->Init();
        game_->GetGlobalEnemyManager()->Clear();
    }
}

void TutorialScene::Draw(sf::RenderWindow& render_window)
{
    map_->Draw(render_window);
    gameObjects_.Draw(render_window, game_->GetCamera());
    gameObjects_.DelayedDraw(render_window, game_->GetCamera());
    pm_.Draw(render_window);
}

void TutorialScene::AddGameObject(GameObject* gameObject)
{
    gameObjects_.Add(gameObject);
}

GameObject* TutorialScene::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    if (byID) return gameObjects_.Find(std::stoi(string));
    else return gameObjects_.Find(string, byTag);
}

void TutorialScene::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void TutorialScene::ChangeScene(const std::string& sceneName)
{
    transitionTo_ = sceneName;
}

void TutorialScene::End()
{
    delete map_;
    gameObjects_.Clear();
    game_->GetTransitionManager()->Clear();
    pm_.Clear();
}