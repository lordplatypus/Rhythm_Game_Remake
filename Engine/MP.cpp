#include "MP.h"
#include <unordered_map>
#include <math.h>
#include <fstream>

std::unordered_map<int, sf::Music> musicMap_;
std::unordered_map<int, sf::SoundBuffer> bufferMap_;
std::unordered_map<int, sf::Sound> soundMap_;

std::unordered_map<int, float> musicBPMMap_;
int playingMusic_{-1};

std::unordered_map<int, int> stageMusicMap_;

MP::MP()
{}

MP::~MP()
{}


//Music

int MP::SetMusic(const int key, const std::string& filePath)
{
    musicMap_[key].openFromFile(filePath);
}

sf::Music* MP::GetMusic(const int key)
{
    return &musicMap_[key];
}

void MP::PlayMusic(const int key, const bool loop)
{ 
    if (musicMap_[GetPlayingMusic()].getStatus() == musicMap_[GetPlayingMusic()].Playing) StopMusic(GetPlayingMusic());
    musicMap_[key].play();
    musicMap_[key].setLoop(loop);
    SetPlayingMusic(key);
}

void MP::PauseMusic(const int key)
{
    musicMap_[key].pause();
}

void MP::StopMusic(const int key)
{
    musicMap_[key].stop();
}

void MP::LoopMusic(const int key, const bool loop)
{
    musicMap_[key].setLoop(loop);
}

void MP::SetPlayingMusic(const int key)
{
    playingMusic_ = key;
}

int MP::GetPlayingMusic()
{
    return playingMusic_;
}

float MP::GetPlayingMusicOffSetInSec()
{
    float temp = musicMap_[GetPlayingMusic()].getPlayingOffset().asSeconds();
    return temp;
}

void MP::RemoveMusic(const int key)
{
    if (musicMap_[key].getStatus() == musicMap_[key].Playing) StopMusic(key);
    soundMap_.erase(key);
}

void MP::ClearMusic()
{
    musicMap_.clear();
}

//For Rhythm Game

float MP::BeatTime()
{
    return fmod(GetPlayingMusicOffSetInSec(), GetBPM(GetPlayingMusic()));
}

void MP::ImportBPM()
{
    std::fstream data("./Resources/Data/BPM.txt");
    char dummy;
    int ID;
    int counter = 0;
    do
    {
        data >> dummy;
        if (dummy == '+')
        {
            counter++;
            data >> ID;
            data >> dummy;
            data >> musicBPMMap_[ID];
        }
    } while (dummy != '!');
    data.close();
}

void MP::SetBPM(const int key, const float BPM)
{
    musicBPMMap_[key] = BPM;

    std::fstream data("./Resources/Data/BPM.txt");
    std::ofstream temp("./Resources/Data/Temp.txt");
    char dummy;
    int ID;
    float dummyNum;
    while(dummy != '!')
    {
        data >> dummy; //move '+'
        temp << dummy;
        if (dummy == '!') break;
        data >> ID; //move ID
        temp << ID;
        data >> dummy; //move ','
        temp << dummy;
        data >> dummyNum; //replace BPM
        temp << musicBPMMap_[ID] << std::endl;
    }
    data.close();
    temp.close();
    remove("./Resources/Data/BPM.txt");
    rename("./Resources/Data/Temp.txt", "./Resources/Data/BPM.txt");
}

float MP::GetBPM(const int key)
{
    return musicBPMMap_[key];
}

void MP::SetStageMusic(const int stageID, const int key)
{
    stageMusicMap_[stageID] = key;
}

void MP::PlayStageMusic(const int stageID, const bool loop)
{
    PlayMusic(stageMusicMap_[stageID], loop);
}


//Sound Effects

int MP::SetSound(const int key, const std::string& filePath)
{
    bufferMap_[key].loadFromFile(filePath);
    soundMap_[key].setBuffer(bufferMap_[key]);
}

void MP::PlaySound(const int key, const bool loop)
{
    soundMap_[key].play();
    soundMap_[key].setLoop(loop);
}

void MP::PauseSound(const int key)
{
    soundMap_[key].pause();
}

void MP::StopSound(const int key)
{
    soundMap_[key].stop();
}

void MP::LoopSound(const int key, const bool loop)
{
    soundMap_[key].setLoop(loop);
}

void MP::RemoveSound(const int key)
{
    if (soundMap_[key].getStatus() == soundMap_[key].Playing) StopSound(key);
    soundMap_.erase(key);
    bufferMap_.erase(key);
}

void MP::ClearSound()
{
    soundMap_.clear();
    bufferMap_.clear();
}