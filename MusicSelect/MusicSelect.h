#ifndef MUSIC_SELECT_H_
#define MUSIC_SELECT_H_
#include <vector>
#include "../Scene/Scene.h"
#include "../Engine/Game.h"
#include "../UI/UIVerticalMenu.h"

class MusicSelect : public Scene
{
public:
    MusicSelect(Game* game);
    ~MusicSelect() override;
    virtual void Init() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void AddGameObject(GameObject* gameObject) override;
    GameObject* FindGameObject(const std::string& string, const bool byTag = true, const bool byID = false) override;
    void ChangeGameObjectOrder(const std::string& name, const std::string& newPos) override;
    void ChangeScene(const std::string& sceneName) override;
    void End() override;

private:
    void StageMenu();
    void MusicMenu();

private:
    enum State {Stage, Music};
    State state = Stage;

    //Background
    int background{0};

    int selectedStage = 0;
    int selectedMusic = 0;

    int instructionText;
    std::vector<int> stageNames_;
    std::vector<int> musicTitles_;
    UIVerticalMenu* stageMenu_{nullptr};
    UIVerticalMenu* musicMenu_{nullptr};

    std::string transitionTo_{""};

    Game* game_ {nullptr};
};

#endif