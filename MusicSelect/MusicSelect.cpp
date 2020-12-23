#include <iostream>
#include "MusicSelect.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"
#include "../Engine/MP.h"
#include "../Engine/IP.h"

MusicSelect::MusicSelect(Game* game) : game_{game}
{}

MusicSelect::~MusicSelect()
{}

void MusicSelect::Init()
{
    game_->GetCamera()->SetTarget(sf::Vector2f(540, 360));
    game_->GetCamera()->SetCameraViewSize(1080.f, 720.f);
    instructionText = LP::SetText("Press up and down to highlight a stage\nPress z to select, Press X to cancel/Go back to Title", sf::Vector2f(32, 32), 16);

    stageNames_.push_back(LP::SetText("Title Music", sf::Vector2f(32, 128), 16));
    stageNames_.push_back(LP::SetText("Lobby Music", sf::Vector2f(32, 128), 16));
    stageNames_.push_back(LP::SetText("Test Map Music", sf::Vector2f(32, 128), 16));
    stageNames_.push_back(LP::SetText("Stage1_1 Music", sf::Vector2f(32, 128), 16));
    stageNames_.push_back(LP::SetText("Stage1_2 Music", sf::Vector2f(32, 128), 16));
    stageNames_.push_back(LP::SetText("Stage1_3 Music", sf::Vector2f(32, 128), 16));
    stageNames_.push_back(LP::SetText("Return to Lobby", sf::Vector2f(32, 128), 16));
    for (auto i : stageNames_) LP::SetTextOriginCenter(i);

    musicTitles_.push_back(LP::SetText("Remember_Passion_Beat", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Necro_Funk_the_Around", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Adjust", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Southern_Arena", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Nothing Can Stop Us Now", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Fight For Your Life", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Amaryllis", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Ayahuasca", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Ceramic Summer", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("La Tropica", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("moonshade_", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Reconfig", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Gain Therapy", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Nec Minus Ultra", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("Il Vento D'oro", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("LAZZULI LUVS", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("DESCENDING AIR CURRENT", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("DETROIT BEAT", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("New Gear", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("across battle result", sf::Vector2f(256, 256), 16));
    for (auto i : musicTitles_) LP::SetTextOriginCenter(i); 

    //Verticle menu setup ()
    stageMenu_ = new UIVerticalMenu(sf::Vector2f(276, 360), stageNames_.size(), stageNames_, 3, 1, 32);
    musicMenu_ = new UIVerticalMenu(sf::Vector2f(804, 360), musicTitles_.size(), musicTitles_, 7, 3, 32);
    musicMenu_->SetDisplay(false);

    //Background
    background = LP::SetSprite(music_select_scene_texture);
}

void MusicSelect::Update(float delta_time, float beat_time)
{
    if (state == Stage)
    {
        StageMenu();
    }
    else if (state == Music)
    {
        MusicMenu();
    }

    //UI update
    stageMenu_->Update(delta_time, beat_time);
    musicMenu_->Update(delta_time, beat_time);

    if (transitionTo_ != "") ChangeScene(transitionTo_);

    if (IP::PressX())
    {
        game_->ChangeScene("Lobby");
    }
}

void MusicSelect::StageMenu()
{
    if (IP::PressUp())
    {
        selectedStage--;
        if (selectedStage < 0) selectedStage = stageNames_.size() - 1;
        stageMenu_->ScrollUp();
    }
    if (IP::PressDown())
    {
        selectedStage++;
        if (selectedStage > stageNames_.size() - 1) selectedStage = 0;
        stageMenu_->ScrollDown();
    }
    if (IP::PressZ())
    {
        if (selectedStage == stageNames_.size() - 1) 
        {
            transitionTo_ = "Lobby";
            return;
        }
        state = Music;
        musicMenu_->SetDisplay(true);
    }
        
}

void MusicSelect::MusicMenu()
{
    if (IP::PressUp())
    {
        selectedMusic--;
        if (selectedMusic < 0) selectedMusic = musicTitles_.size() - 1;
        musicMenu_->ScrollUp();
    }
    if (IP::PressDown())
    {
        selectedMusic++;
        if (selectedMusic > musicTitles_.size() - 1) selectedMusic = 0;
        musicMenu_->ScrollDown();
    }
    if (IP::PressZ())
    {
        MP::SetStageMusic(selectedStage, selectedMusic);
        MP::PlayMusic(selectedMusic, true);
        state = Stage;
        musicMenu_->SetDisplay(false);
    }
    if (IP::PressX())
    {
        state = Stage;
        musicMenu_->SetDisplay(false);
    }
}


void MusicSelect::Draw(sf::RenderWindow& render_window)
{
    render_window.draw(background);
    render_window.draw(instructionText);
    //Draw UI
    stageMenu_->Draw(render_window);
    musicMenu_->Draw(render_window);
}

void MusicSelect::AddGameObject(GameObject* gameObject)
{}

GameObject* MusicSelect::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    return nullptr;
}

void MusicSelect::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void MusicSelect::ChangeScene(const std::string& sceneName)
{
    game_->ChangeScene(sceneName);
}

void MusicSelect::End()
{
    selectedMusic = 0;
    selectedStage = 0;

    stageNames_.clear();

    //delete music titles text ()
    musicTitles_.clear();

    delete stageMenu_;
    delete musicMenu_;
}