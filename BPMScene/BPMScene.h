#ifndef BPM_SCENE_H_
#define BPM_SCENE_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Scene/Scene.h"
#include "../Engine/MP.h"
#include "../Engine/Game.h"
#include "../UI/UIVerticalMenu.h"

class BPMScene : public Scene
{
public:
    BPMScene(Game* game);
    ~BPMScene() override;
    void Init() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void AddGameObject(GameObject* gameObject) override;
    GameObject* FindGameObject(const std::string& string, const bool byTag = true, const bool byID = false) override;
    void ChangeGameObjectOrder(const std::string& name, const std::string& newPos) override;
    void ChangeScene(const std::string& sceneName) override;
    void End() override;

private:
    void ImportBPM();
    void MainMenu();
    void MusicSelectMenu();
    void BPMSetUp();
    void MusicPlayBack(float delta_time, float beat_time);
    void SaveBPMForSelectedSong();

private:
    //Background
    int background;

    //enum for states
    enum State {Menu, MusicSelect, SetUp, PlayBack, Save};
    State state = Menu;

    //Menu Text
    std::vector<int> menuText_;
    std::vector<int> musicTitles_;
    int selectedOption = 0;
    int setupInstructions;
    //int playbackInstructions;
    int savedText;
    int displayMusicTitle;
    int displayBeatsPerMin;
    int displaySecPerBeat;
    int displayBeatTimer;
    int displayBeatCount;
    float alpha{0};
    UIVerticalMenu* menu_{nullptr};
    UIVerticalMenu* musicMenu_{nullptr};

    //Music Select
    int musicID = 0;
    int selectedMusicID = 0;

    //Numbers
    std::vector<float> listOfBeats;
    float beatsPerMin{0};
    float secPerBeat{0};
    float beatTimer{0};
    float zeroOutTime{0};
    int count{0};

    std::unordered_map<int, float> musicSPBMap;

    //Play Back
    std::vector<int> playerSprite;
    std::vector<int> heartSprite;

    //for Player
    float timer{0};
    float timeInbetweenFrames{0};
    int animCount = 0;

    //For heart
    int heartCount{0};
    bool oneTime{false};

    bool pressedUp = false;
    bool pressedDown = false;
    bool pressedRight = false;
    bool pressedLeft = false;
    bool pressedZ = true;
    bool pressedX = true;

    bool firstTime = true;

    Game* game_ {nullptr};
};

#endif