#ifndef BPM_SCENE_H_
#define BPM_SCENE_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Scene/Scene.h"
#include "../Engine/Game.h"
#include "../UI/UIVerticalMenu.h"

class BPMScene : public Scene
{
public:
    BPMScene(Game* game);
    ~BPMScene() override;
    void Init() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(sf::RenderWindow& render_window) override;
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
    sf::Sprite background;

    //enum for states
    enum State {Menu, MusicSelect, SetUp, PlayBack, Save};
    State state = Menu;

    //Menu Text
    std::vector<sf::Text> menuText_;
    std::vector<sf::Text> musicTitles_;
    int selectedOption = 0;
    sf::Text instructions;
    //int playbackInstructions;
    sf::Text savedText;
    sf::Text displayMusicTitle;
    sf::Text displayBeatsPerMin;
    sf::Text displaySecPerBeat;
    sf::Text displayBeatTimer;
    sf::Text displayBeatCount;
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
    std::vector<sf::Sprite> playerSprite;
    std::vector<sf::Sprite> heartSprite;

    //for Player
    float timer{0};
    float timeInbetweenFrames{0};
    int animCount = 0;

    //For heart
    int heartCount{0};
    bool oneTime{false};

    bool firstTime = true;

    Game* game_ {nullptr};

    //transition
    std::string transitionTo_{""};
};

#endif