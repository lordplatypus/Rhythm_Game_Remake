#include <cmath>
#include <fstream>
#include "BPMScene.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/IP.h"



BPMScene::BPMScene(Game* game) : game_{game}
{}

BPMScene::~BPMScene()
{}

void BPMScene::Init()
{
    game_->GetCamera()->SetCameraViewSize(1080.0f, 720.0f);
    game_->GetCamera()->SetTarget(sf::Vector2f(540.0f, 360.0f));

    //Create Text for the main menu (メインメニューのテクストを設定する)
    menuText_.push_back(LP::SetText("Choose Music", sf::Vector2f(256, 256), 16));
    menuText_.push_back(LP::SetText("Start BPM Setup", sf::Vector2f(256, 256), 16));
    menuText_.push_back(LP::SetText("Start Playback", sf::Vector2f(256, 256), 16));
    menuText_.push_back(LP::SetText("Save Changes", sf::Vector2f(256, 256), 16));
    menuText_.push_back(LP::SetText("Quit", sf::Vector2f(256, 256), 16));
    for (auto i : menuText_) LP::SetTextOriginCenter(i); //set the origin to the center (テクストの原点を設定する)

    //Duplicate the music titles (text) from the MP class
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
    menu_ = new UIVerticalMenu(sf::Vector2f(275, 183), menuText_.size(), menuText_, 3, 1, 32);
    musicMenu_ = new UIVerticalMenu(sf::Vector2f(803, 183), musicTitles_.size(), musicTitles_, 5, 2, 32);
    musicMenu_->SetDisplay(false);

    //Set up the rest of the text used (残るテクストを設定する)
    setupInstructions = LP::SetText("Z to start,\n\nDown to time beats,\n\nX to return", sf::Vector2f(584+16, 88+16), 16);
    savedText = LP::SetText("Saved", sf::Vector2f(803, 183), 16);
    LP::SetTextOriginCenter(savedText);
    displayMusicTitle = LP::SetText("Music Title: NA", sf::Vector2f(96, 448), 16);
    displayBeatsPerMin = LP::SetText("Beats Per Min: NA", sf::Vector2f(96, 480), 16);
    //secPerBeat = MP::GetBPMForSelectedMusic(musicID);
    displaySecPerBeat = LP::SetText("Beats Per Sec: NA", sf::Vector2f(96, 512), 16);
    displayBeatTimer = LP::SetText("0", sf::Vector2f(96, 544), 16);
    displayBeatCount = LP::SetText("0", sf::Vector2f(96, 576), 16);

    //setup background picture ()
    background = LP::SetSprite(bps_scene_texture, sf::Vector2f(0, 0));

    //setup sprites used for timing (スプライトを設定する)
    heartSprite = LP::SetSprite(heart_texture, 16, 16, 2, 1); //heart sprite (ハートのスプライト)
    for (auto i : heartSprite) 
    {
        LP::SetSpriteScale(i, 8, 8); //set heart sprite scale ()
        LP::SetSpriteOriginCenter(i);
    }
    playerSprite = LP::SetSprite(roboko_texture, 32, 32, 6, 1); //char sprite (キャラクターのスプライト)
    for (auto i : playerSprite) 
    {
        LP::SetSpriteScale(i, 6, 6); //set char sprite scale ()
        LP::SetSpriteOriginCenter(i);
    }

    //Import data into "MusicSPBMap"
    ImportBPM();
}

void BPMScene::ImportBPM()
{
    std::fstream data("./Resources/Data/BPM.txt");
    char dummy;
    int ID;
    do
    {
        data >> dummy;
        if (dummy == '+')
        {
            data >> ID;
            data >> dummy;
            data >> musicSPBMap[ID];
        }
    } while (dummy != '!');
    data.close();
}

void BPMScene::Update(float delta_time, float beat_time)
{
    if (state == Menu)
    {//Main menu (マインメニュー)
        MainMenu();
    }
    else if (state == MusicSelect)
    {//Music select (音楽選択)
        MusicSelectMenu();
    }
    else if (state == SetUp)
    {//Setup the BPM for selected song (選択した音楽のBPMを設定する)
        BPMSetUp();
    }
    else if (state == PlayBack)
    {//Play back the selected song
        MusicPlayBack(delta_time, beat_time);
    }
    else if (state == Save)
    {//save new BPM
        SaveBPMForSelectedSong();
    }

    //for 'saved' text fade out
    if (alpha > 0) 
    {
        alpha -= 200 * delta_time;
        LP::SetTextColor(savedText, 255, 255, 255, alpha);
    }
    else alpha = 0;

    //UI update
    menu_->Update(delta_time, beat_time);
    musicMenu_->Update(delta_time, beat_time);
}

void BPMScene::MainMenu()
{
    if (IP::PressUp())
    {
        selectedOption--;
        if (selectedOption < 0) selectedOption = menuText_.size() - 1;
        menu_->ScrollUp();
        pressedUp = true;
    }
    if (IP::PressDown())
    {
        selectedOption++;
        if (selectedOption > menuText_.size() - 1) selectedOption = 0;
        menu_->ScrollDown();
        pressedDown = true;
    }
    if (IP::PressZ())
    {
        if (selectedOption == 0) 
        {
            state = MusicSelect;
            musicMenu_->SetDisplay(true);
        }
        if (selectedOption == 1) state = SetUp;
        if (selectedOption == 2) state = PlayBack;
        if (selectedOption == 3) state = Save;
        if (selectedOption == 4) game_->ChangeScene("Lobby");
        pressedZ = true;
    }
    if (IP::PressX())
    {
        game_->ChangeScene("Lobby");
        pressedX = true;
    }
}

void BPMScene::MusicSelectMenu()
{
    if (IP::PressUp())
    {
        musicID--;
        if (musicID < 0) musicID = musicTitles_.size() - 1;
        musicMenu_->ScrollUp();
        pressedUp = true;
    }
    if (IP::PressDown())
    {
        musicID++;
        if (musicID > musicTitles_.size() - 1) musicID = 0;
        musicMenu_->ScrollDown();
        pressedDown = true;
    }
    if (IP::PressZ())
    {
        selectedMusicID = musicID;

        //LP::SetTextString(displayMusicTitle, MP::GetMusicTitle(selectedMusicID));
        LP::SetTextString(displayBeatsPerMin, "Beats Per Min: " + std::to_string((int)round(60 / musicSPBMap[musicID])));
        LP::SetTextString(displaySecPerBeat, "Beats Per Sec: " + std::to_string(musicSPBMap[selectedMusicID]));
        LP::SetTextString(displayBeatTimer, "Beat Time: 0");
        LP::SetTextString(displayBeatCount, "Beat Count: 0");

        state = Menu;
        musicMenu_->SetDisplay(false);
        pressedZ = true;
    }
    if (IP::PressX())
    {
        musicID = selectedMusicID;
        state = Menu;
        musicMenu_->SetDisplay(false);
        pressedX = true;
    }
}

void BPMScene::BPMSetUp()
{
    if (IP::PressZ())
    {//reset variables
        MP::PlayMusic(musicID, false);
        pressedZ = true;
        secPerBeat = 0;
        beatsPerMin = 0;
        beatTimer = 0;
        zeroOutTime = 0;
        count = 0;
        listOfBeats.clear();
    }

    if (IP::PressDown())
    {
        if (firstTime == true)
        {
            zeroOutTime = MP::GetPlayingMusicOffSetInSec();
            firstTime = false;
        }
        else
        { 
            beatTimer = MP::GetPlayingMusicOffSetInSec() - zeroOutTime;
            zeroOutTime = MP::GetPlayingMusicOffSetInSec();

            listOfBeats.push_back(beatTimer);
            //secPerBeat = 0;
            musicSPBMap[musicID] = 0;
            //for (auto i : listOfBeats) secPerBeat += i;
            for (auto i : listOfBeats) musicSPBMap[musicID] += i;
            //secPerBeat /= listOfBeats.size(); //average time inbetween beats
            musicSPBMap[musicID] /= listOfBeats.size();
            //if (secPerBeat != 0) beatsPerMin = (int)round(60 / secPerBeat); //BPM
            if (musicSPBMap[musicID] != 0) 
            {
                beatsPerMin = round(60 / musicSPBMap[musicID]);
                secPerBeat = musicSPBMap[musicID];
                LP::SetTextString(displayBeatsPerMin, "Beats Per Min: " + std::to_string((int)beatsPerMin));
                LP::SetTextString(displaySecPerBeat, "Beats Per Sec: " + std::to_string(secPerBeat));
            }
        }

        pressedDown = true;
        count++; //for beat count
    }

    if (IP::PressX())
    {
        firstTime = true;
        state = Menu;
        pressedX = true;
    }
}

void BPMScene::MusicPlayBack(float delta_time, float beat_time)
{
    if (IP::PressUp())
    {
        musicSPBMap[musicID] = 60 / (60 / musicSPBMap[musicID] + 1);
        secPerBeat = musicSPBMap[musicID];
        beatsPerMin = (int)round(60 / musicSPBMap[musicID]);
        timeInbetweenFrames = musicSPBMap[musicID] / 10;
        LP::SetTextString(displayBeatsPerMin, "Beats Per Min: " + std::to_string((int)round(60 / musicSPBMap[musicID])));
        LP::SetTextString(displaySecPerBeat, "Beats Per Sec: " + std::to_string(musicSPBMap[selectedMusicID]));
        pressedUp = true;
    }
    if (IP::PressDown())
    {
        musicSPBMap[musicID] = 60 / (60 / musicSPBMap[musicID] - 1);
        secPerBeat = musicSPBMap[musicID];
        beatsPerMin = (int)round(60 / musicSPBMap[musicID]);
        timeInbetweenFrames = musicSPBMap[musicID] / 10;
        LP::SetTextString(displayBeatsPerMin, "Beats Per Min: " + std::to_string((int)round(60 / musicSPBMap[musicID])));
        LP::SetTextString(displaySecPerBeat, "Beats Per Sec: " + std::to_string(musicSPBMap[selectedMusicID]));
        pressedDown = true;
    }

    if (firstTime)
    {//reset variables
        MP::PlayMusic(musicID);
        secPerBeat = MP::GetBPM(musicID);
        beatsPerMin = (int)round(60 / musicSPBMap[musicID]);
        animCount = 0;
        count = 0;
        timeInbetweenFrames = secPerBeat / 10;
        LP::SetTextString(displayBeatsPerMin, "Beats Per Min: " + std::to_string((int)round(60 / musicSPBMap[musicID])));
        LP::SetTextString(displaySecPerBeat, "Beats Per Sec: " + std::to_string(musicSPBMap[selectedMusicID]));
        firstTime = false;
    }

    beatTimer = fmod(MP::GetPlayingMusicOffSetInSec(), musicSPBMap[musicID]);
    //beatTimer = beat_time;

    //Heart Animation
    if (oneTime && beatTimer <= timeInbetweenFrames)
    {
        if (heartCount == 0) heartCount = 1;
        else heartCount = 0;
        oneTime = false;
        count++;
    }
    else if (beatTimer > timeInbetweenFrames) oneTime = true;

    //Player Animation
    timer += delta_time;
    if (beatTimer <= timeInbetweenFrames) animCount = 0;     
    else if (animCount != 5 && timer >= timeInbetweenFrames) 
    {
        animCount++;
        timer = 0;
    }

    if (IP::PressX())
    {
        count = 0;
        LP::SetTextString(displayBeatTimer, "Beat Time: 0");
        LP::SetTextString(displayBeatCount, "Beat Count: 0");
        firstTime = true;
        state = Menu;
        pressedX = true;
    }
}

void BPMScene::SaveBPMForSelectedSong()
{
    // secPerBeat = 0;
    // if (listOfBeats.size() != 0)
    // {
    //     for (auto i : listOfBeats) secPerBeat += i;
    //     secPerBeat /= listOfBeats.size(); //average time inbetween beats
    // }
    // if (secPerBeat != 0)
    // {
    //     MP::SetBPMForSelectedMusic(musicID, secPerBeat);
    //     alpha = 255; //for 'saved' text fade out
    // }

    if (musicSPBMap[musicID] != 0)
    {
        MP::SetBPM(musicID, musicSPBMap[musicID]);
        alpha = 255;
    }
    state = Menu;
}

void BPMScene::Draw()
{
    //Draw Background
    LP::DrawSprite(background);

    //Draw different things at different states
    if (state == Menu)
    {
        LP::DrawText(displayMusicTitle);
        LP::DrawText(displayBeatsPerMin);
        LP::DrawText(displaySecPerBeat);
        LP::DrawText(displayBeatTimer);
        LP::DrawText(displayBeatCount);

        LP::DrawSprite(playerSprite[0], sf::Vector2f(901, 535));
        LP::DrawSprite(heartSprite[0], sf::Vector2f(705, 535));
    }

    else if (state == MusicSelect)
    {
        LP::DrawText(displayMusicTitle);
        LP::DrawText(displayBeatsPerMin);
        LP::DrawText(displaySecPerBeat);
        LP::DrawText(displayBeatTimer);
        LP::DrawText(displayBeatCount);

        LP::DrawSprite(playerSprite[0], sf::Vector2f(901, 535));
        LP::DrawSprite(heartSprite[0], sf::Vector2f(705, 535));
    }

    else if (state == SetUp)
    {
        LP::DrawText(setupInstructions);
        LP::DrawText(displayMusicTitle);
        LP::DrawText(displayBeatsPerMin);
        LP::DrawText(displaySecPerBeat);
        LP::DrawText(displayBeatTimer, "Beat Time: " + std::to_string(beatTimer));
        LP::DrawText(displayBeatCount, "Beat Count: " + std::to_string(count));
        LP::DrawSprite(playerSprite[0], sf::Vector2f(901, 535));
        LP::DrawSprite(heartSprite[0], sf::Vector2f(705, 535));
    }

    else if (state == PlayBack)
    {
        LP::DrawText(displayMusicTitle);
        LP::DrawText(displayBeatsPerMin);
        LP::DrawText(displaySecPerBeat);
        LP::DrawText(displayBeatTimer, "Beat Time: " + std::to_string(beatTimer));
        LP::DrawText(displayBeatCount, "Beat Count: " + std::to_string(count));
        LP::DrawSprite(playerSprite[animCount], sf::Vector2f(901, 535));
        LP::DrawSprite(heartSprite[heartCount], sf::Vector2f(705, 535));
    }

    else if (state == Save)
    {}

    if (alpha > 0) LP::DrawText(savedText); //draw 'saved' text when visible

    //Draw UI
    menu_->Draw();
    musicMenu_->Draw();
}

void BPMScene::AddGameObject(GameObject* gameObject)
{}

GameObject* BPMScene::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{}

void BPMScene::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void BPMScene::ChangeScene(const std::string& sceneName)
{
    game_->ChangeScene(sceneName);
}

void BPMScene::End()
{
    selectedOption = 0;
    musicID = 0;

    //delete main menu text (マインメニューテクストを削除する)
    for (auto i : menuText_)
    {
        LP::DeleteText(i);
    }
    menuText_.clear();

    //delete music titles text ()
    for (auto i : musicTitles_)
    {
        LP::DeleteText(i);
    }
    musicTitles_.clear();

    //delete other text (他のテクストを削除する)
    LP::DeleteText(setupInstructions);
    LP::DeleteText(displayBeatCount);
    LP::DeleteText(displayBeatsPerMin);
    LP::DeleteText(displaySecPerBeat);
    LP::DeleteText(savedText);

    //delete heart sprite (ハートのスパライトを削除する)
    for(auto i : heartSprite)
    {
        LP::DeleteSprite(i);
    }
    heartSprite.clear();

    //delete char sprite (キャラクターのスパライトを削除する)
    for(auto i : playerSprite)
    {
        LP::DeleteSprite(i);
    }
    playerSprite.clear();

    LP::DeleteSprite(background);

    delete menu_;
    delete musicMenu_;
}