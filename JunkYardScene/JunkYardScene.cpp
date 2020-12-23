#include "JunkYardScene.h"
#include "JunkYardMap.h"
#include "../Engine/LP.h"
#include "../Engine/IP.h"
#include "../Engine/Math.h"

JunkYardScene::JunkYardScene(Game* game) : game_{game}
{}

JunkYardScene::~JunkYardScene()
{}

void JunkYardScene::Init()
{
    game_->GetTransitionManager()->SetCurrentScene("JunkYard");
    map_ = new JunkYardMap(this, game_->GetCamera(), game_->GetPlayerManager(), game_->GetTransitionManager(), &pm_);
    game_->GetCamera()->SetCameraViewSize(360.f, 240.f);
    game_->GetCamera()->SetTarget(gameObjects_.Find("Player")->GetPosition());
    pm_.FadeFromBlack(gameObjects_.Find("Player")->GetPosition().x, gameObjects_.Find("Player")->GetPosition().y);
    transitionTo_ = "";
}

void JunkYardScene::Update(float delta_time, float beat_time)
{
    gameObjects_.Update(delta_time, beat_time);
    gameObjects_.Collision();
    gameObjects_.Perception();
    gameObjects_.Remove();
    pm_.Update(delta_time);

    if (gameObjects_.Find("Player") != nullptr) 
        game_->GetCamera()->SetTarget(Math::Lerp(game_->GetCamera()->GetCameraCenter(), gameObjects_.Find("Player")->GetPosition() + sf::Vector2f(8, 8), 10 * delta_time));

    if (transitionTo_ != "") game_->ChangeScene(transitionTo_);

    if (IP::PressX())
    {//Return to TitleScene
        game_->ChangeScene("Title");
    }
}

void JunkYardScene::Draw(sf::RenderWindow& render_window)
{
    map_->Draw(render_window);
    gameObjects_.Draw(render_window);
    gameObjects_.DelayedDraw(render_window);
    pm_.Draw(render_window);
}

void JunkYardScene::AddGameObject(GameObject* gameObject)
{
    gameObjects_.Add(gameObject);
}

GameObject* JunkYardScene::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    if (byID) return gameObjects_.Find(std::stoi(string));
    else return gameObjects_.Find(string, byTag);
}

void JunkYardScene::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void JunkYardScene::ChangeScene(const std::string& sceneName)
{
    transitionTo_ = sceneName;
}

void JunkYardScene::End()
{
    delete map_;
    gameObjects_.Clear();
    pm_.Clear();
}