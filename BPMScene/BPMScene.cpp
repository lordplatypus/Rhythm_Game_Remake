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
    for (int i = 0; i < menuText_.size(); i++) LP::SetTextOriginCenter(&menuText_[i]); //set the origin to the center (テクストの原点を設定する)

    //Duplicate the music titles (text) from the MP class
    // musicTitles_.push_back(LP::SetText("Remember_Passion_Beat", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Necro_Funk_the_Around", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Adjust", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Southern_Arena", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Nothing Can Stop Us Now", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Fight For Your Life", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Amaryllis", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Ayahuasca", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Ceramic Summer", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("La Tropica", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("moonshade_", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Reconfig", sf::Vector2f(256, 256), 16));
    //musicTitles_.push_back(LP::SetText("Gain Therapy", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Nec Minus Ultra", sf::Vector2f(256, 256), 16));
    // musicTitles_.push_back(LP::SetText("Il Vento D'oro", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("LAZZULI LUVS", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("DESCENDING AIR CURRENT", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("DETROIT BEAT", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("New Gear", sf::Vector2f(256, 256), 16));
    musicTitles_.push_back(LP::SetText("across battle result", sf::Vector2f(256, 256), 16));
    for (int i = 0; i < musicTitles_.size(); i++) LP::SetTextOriginCenter(&musicTitles_[i]);

    //Verticle menu setup ()
    menu_ = new UIVerticalMenu(sf::Vector2f(275, 183), menuText_.size(), menuText_, 3, 1, 32);
    musicMenu_ = new UIVerticalMenu(sf::Vector2f(803, 183), musicTitles_.size(), musicTitles_, 3, 1, 32);
    musicMenu_->SetDisplay(false);

    //Set up the rest of the text used (残るテクストを設定する)
    instructions = LP::SetText("Use Up and Down to\n\ncycle through options\n\nZ to select an option,\n\nX to return to lobby", sf::Vector2f(584+32, 88), 16);
    savedText = LP::SetText("Saved", game_->GetCamera()->GetCameraCenter(), 32);
    LP::SetTextOriginCenter(&savedText);
    displayMusicTitle = LP::SetText("Music Title: NA", sf::Vector2f(96, 448), 16);
    displayBeatsPerMin = LP::SetText("Beats Per Min: NA", sf::Vector2f(96, 480), 16);
    //secPerBeat = MP::GetBPMForSelectedMusic(musicID);
    displaySecPerBeat = LP::SetText("Beats Per Sec: NA", sf::Vector2f(96, 512), 16);
    displayBeatTimer = LP::SetText("0", sf::Vector2f(96, 544), 16);
    displayBeatCount = LP::SetText("0", sf::Vector2f(96, 576), 16);

    //setup background picture ()
    background = LP::SetSprite(bps_scene_texture, sf::Vector2f(0, 0));

    //setup sprites used for timing (スプライトを設定する)
    heartSprite = LP::SetMultiFrameSprite(hearts_texture, 16, 16, 2, 1, sf::Vector2f(705, 535)); //heart sprite (ハートのスプライト)
    for (int i = 0; i < heartSprite.size(); i++) 
    {
        heartSprite[i].setScale(8.0f, 8.0f); //set heart sprite scale ()
        LP::SetSpriteOriginCenter(&heartSprite[i]);
    }
    playerSprite = LP::SetMultiFrameSprite(roboko_texture, 32, 32, 6, 1, sf::Vector2f(901, 535)); //char sprite (キャラクターのスプライト)
    for (int i = 0; i < playerSprite.size(); i++) 
    {
        playerSprite[i].setScale(6.0f, 6.0f); //set char sprite scale ()
        LP::SetSpriteOriginCenter(&playerSprite[i]);
    }

    //transition
    transitionTo_ = "";

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
        savedText.setFillColor(sf::Color(255, 255, 255, alpha));
    }
    else alpha = 0;

    //UI update
    menu_->Update(delta_time, beat_time);
    musicMenu_->Update(delta_time, beat_time);

    if (transitionTo_ != "") game_->ChangeScene(transitionTo_);

    if (IP::PressX()) game_->ChangeScene("Lobby");
}

void BPMScene::MainMenu()
{
    if (IP::PressUp())
    {
        selectedOption--;
        if (selectedOption < 0) selectedOption = menuText_.size() - 1;
        menu_->ScrollUp();
    }
    if (IP::PressDown())
    {
        selectedOption++;
        if (selectedOption > menuText_.size() - 1) selectedOption = 0;
        menu_->ScrollDown();
    }
    if (IP::PressZ())
    {
        if (selectedOption == 0) 
        {
            state = MusicSelect;
            musicMenu_->SetDisplay(true);
        }
        if (selectedOption == 1) 
        {
            state = SetUp;
            instructions.setString("Z to start,\n\nDown to time beats,\n\nX to return");
        }
        if (selectedOption == 2) 
        {
            state = PlayBack;
            instructions.setString("Use Up and Down\n\nto tweak the BPM,\n\nX to return");
        }
        if (selectedOption == 3) state = Save;
        if (selectedOption == 4) transitionTo_ = "Lobby";
    }
}

void BPMScene::MusicSelectMenu()
{
    if (IP::PressUp())
    {
        musicID--;
        if (musicID < 0) musicID = musicTitles_.size() - 1;
        musicMenu_->ScrollUp();
    }
    if (IP::PressDown())
    {
        musicID++;
        if (musicID > musicTitles_.size() - 1) musicID = 0;
        musicMenu_->ScrollDown();
    }
    if (IP::PressZ())
    {
        selectedMusicID = musicID;

        //LP::SetTextString(displayMusicTitle, MP::GetMusicTitle(selectedMusicID));
        displayMusicTitle.setString(musicTitles_[selectedMusicID].getString());
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string((int)round(60 / musicSPBMap[musicID])));
        displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(musicSPBMap[selectedMusicID]));
        displayBeatTimer.setString("Beat Time: 0");
        displayBeatCount.setString("Beat Count: 0");

        instructions.setString("Use Up and Down\n\nto cycle through options,\n\nZ to select an option,\n\nX to return to lobby");

        state = Menu;
        musicMenu_->SetDisplay(false);
    }
    if (IP::PressX())
    {
        musicID = selectedMusicID;
        instructions.setString("Use Up and Down\n\nto cycle through options,\n\nZ to select an option,\n\nX to return to lobby");
        state = Menu;
        musicMenu_->SetDisplay(false);
    }
}

void BPMScene::BPMSetUp()
{
    if (IP::PressZ())
    {//reset variables
        MP::PlayMusic(musicID, false);
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
                displayBeatsPerMin.setString("Beats Per Min: " + std::to_string((int)beatsPerMin));
                displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(secPerBeat));
            }
        }
        count++; //for beat count
    }

    displayBeatTimer.setString("Beat Time: " + std::to_string(beatTimer));
    displayBeatCount.setString("Beat Count: " + std::to_string(count));

    if (IP::PressX())
    {
        firstTime = true;
        state = Menu;
        instructions.setString("Use Up and Down\n\nto cycle through options,\n\nZ to select an option,\n\nX to return to lobby");
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
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string((int)round(60 / musicSPBMap[musicID])));
        displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(musicSPBMap[selectedMusicID]));
    }
    if (IP::PressDown())
    {
        musicSPBMap[musicID] = 60 / (60 / musicSPBMap[musicID] - 1);
        secPerBeat = musicSPBMap[musicID];
        beatsPerMin = (int)round(60 / musicSPBMap[musicID]);
        timeInbetweenFrames = musicSPBMap[musicID] / 10;
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string((int)round(60 / musicSPBMap[musicID])));
        displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(musicSPBMap[selectedMusicID]));
    }

    if (firstTime)
    {//reset variables
        MP::PlayMusic(musicID);
        secPerBeat = MP::GetBPM(musicID);
        beatsPerMin = (int)round(60 / musicSPBMap[musicID]);
        animCount = 0;
        count = 0;
        timeInbetweenFrames = secPerBeat / 10;
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string((int)round(60 / musicSPBMap[musicID])));
        displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(musicSPBMap[selectedMusicID]));
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

    displayBeatTimer.setString("Beat Time: " + std::to_string(beatTimer));
    displayBeatCount.setString("Beat Count: " + std::to_string(count));

    if (IP::PressX())
    {
        count = 0;
        displayBeatTimer.setString("Beat Time: 0");
        displayBeatCount.setString("Beat Count: 0");
        firstTime = true;
        state = Menu;
        instructions.setString("Use Up and Down\n\nto cycle through options,\n\nZ to select an option,\n\nX to return to lobby");
    }
}

void BPMScene::SaveBPMForSelectedSong()
{
    if (musicSPBMap[musicID] != 0)
    {
        MP::SetBPM(musicID, musicSPBMap[musicID]);
        alpha = 255;
    }
    state = Menu;
}

void BPMScene::Draw(sf::RenderWindow& render_window)
{
    //Draw Background
    render_window.draw(background);

    //Draw different things at different states
    if (state == Menu)
    {
        render_window.draw(instructions);
        render_window.draw(displayMusicTitle);
        render_window.draw(displayBeatsPerMin);
        render_window.draw(displaySecPerBeat);
        render_window.draw(displayBeatTimer);
        render_window.draw(displayBeatCount);

        render_window.draw(playerSprite[0]);
        render_window.draw(heartSprite[0]);
    }

    else if (state == MusicSelect)
    {
        render_window.draw(displayMusicTitle);
        render_window.draw(displayBeatsPerMin);
        render_window.draw(displaySecPerBeat);
        render_window.draw(displayBeatTimer);
        render_window.draw(displayBeatCount);

        render_window.draw(playerSprite[0]);
        render_window.draw(heartSprite[0]);
    }

    else if (state == SetUp)
    {
        render_window.draw(instructions);
        render_window.draw(displayMusicTitle);
        render_window.draw(displayBeatsPerMin);
        render_window.draw(displaySecPerBeat);
        render_window.draw(displayBeatTimer);
        render_window.draw(displayBeatCount);
        render_window.draw(playerSprite[0]);
        render_window.draw(heartSprite[0]);
    }

    else if (state == PlayBack)
    {
        render_window.draw(instructions);
        render_window.draw(displayMusicTitle);
        render_window.draw(displayBeatsPerMin);
        render_window.draw(displaySecPerBeat);
        render_window.draw(displayBeatTimer);
        render_window.draw(displayBeatCount);
        render_window.draw(playerSprite[animCount]);
        render_window.draw(heartSprite[heartCount]);
    }

    else if (state == Save)
    {}

    if (alpha > 0) render_window.draw(savedText); //draw 'saved' text when visible

    //Draw UI
    menu_->Draw(render_window);
    musicMenu_->Draw(render_window);
}

void BPMScene::AddGameObject(GameObject* gameObject)
{}

GameObject* BPMScene::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    return nullptr;
}

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
    menuText_.clear();

    //delete music titles text ()
    musicTitles_.clear();

    //delete other text (他のテクストを削除する)

    //delete heart sprite (ハートのスパライトを削除する)
    heartSprite.clear();

    //delete char sprite (キャラクターのスパライトを削除する)
    playerSprite.clear();

    delete menu_;
    delete musicMenu_;
}