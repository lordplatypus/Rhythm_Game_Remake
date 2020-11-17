#include "TransitionManager.h"

TransitionManager::TransitionManager()
{}

TransitionManager::~TransitionManager()
{}

void TransitionManager::Add(const std::string& name, const bool locked)
{
    transitions_[name] = locked;
}

void TransitionManager::Lock(const std::string& name)
{
    transitions_[name] = true;
}

void TransitionManager::Unlock(const std::string& name)
{
    transitions_[name] = false;
}

bool TransitionManager::IsLocked(const std::string& name)
{
    return transitions_[name];
}



void TransitionManager::SetCurrentScene(const std::string& name)
{
    SetPrevScene(currentScene_);
    currentScene_ = name;
}

const std::string& TransitionManager::GetCurrentScene()
{
    return currentScene_;
}

void TransitionManager::SetPrevScene(const std::string& name)
{
    prevScene_ = name;
}

const std::string& TransitionManager::GetPrevScene()
{
    return prevScene_;
}

// int TransitionManager::GetSceneID(const std::string& name) const
// {
//     if (name == "Title") return 200;
//     else if (name == "Lobby") return 201;
//     else if (name == "ClassSelect") return 202;
//     else if (name == "SetBPM") return 203;
//     else if (name == "MusicSelect") return 204;
//     else if (name == "Tutorial") return 205;
//     else if (name == "Test") return 206;
//     else if (name == "JunkYard") return 207;
//     else if (name == "Stage1_1") return 208;
//     else if (name == "Stage1_2") return 209;
//     else if (name == "Stage1_3") return 210;

//     return 200; //if the name provided dosen't exist - go to the Title
// }



void TransitionManager::Clear()
{
    transitions_.clear();
}