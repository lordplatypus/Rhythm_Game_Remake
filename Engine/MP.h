#ifndef MP_H_
#define MP_H_
#include <SFML/Audio.hpp>

class MP
{
public:
    MP();
    ~MP();
    //Music
    static int SetMusic(const int key, const std::string& filePath);
    static sf::Music* GetMusic(const int key);
    static void PlayMusic(const int key, const bool loop = false);
    static void PauseMusic(const int key);
    static void StopMusic(const int key);
    static void LoopMusic(const int key, const bool loop);

    static void SetPlayingMusic(const int key);
    static int GetPlayingMusic();
    static float GetPlayingMusicOffSetInSec();

    static void RemoveMusic(const int key);
    static void ClearMusic();

    //For Rhythm Game
    static float BeatTime();
    static void ImportBPM();
    static void SetBPM(const int key, const float BPM);
    static float GetBPM(const int key);
    static void SetStageMusic(const int stageID, const int key);
    static void PlayStageMusic(const int stageID, const bool loop = false);

    //Sound Effects
    static int SetSound(const int key, const std::string& filePath);
    static void PlaySound(const int key, const bool loop = false);
    static void PauseSound(const int key);
    static void StopSound(const int key);
    static void LoopSound(const int key, const bool loop);
    static void RemoveSound(const int key);
    static void ClearSound();
};

#endif