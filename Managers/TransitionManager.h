#ifndef TRANSITION_MANAGER_H_
#define TRANSITION_MANAGER_H_
#include <unordered_map>

class TransitionManager
{
public:
    TransitionManager();
    ~TransitionManager();
    
    void Add(const std::string& name, const bool locked);
    void Lock(const std::string& name);
    void Unlock(const std::string& name);
    bool IsLocked(const std::string& name);

    void SetCurrentScene(const std::string& name);
    const std::string& GetCurrentScene();
    void SetPrevScene(const std::string& name);
    const std::string& GetPrevScene();

    //int GetSceneID(const std::string& name) const;

    void Clear();

private:
    std::unordered_map<std::string, bool> transitions_;
    std::string currentScene_{""};
    std::string prevScene_{""};
};

#endif