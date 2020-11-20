#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{}

GameObjectManager::~GameObjectManager()
{
    Clear();
}

void GameObjectManager::Add(GameObject* gameObject)
{
    gameObjects_.push_back(gameObject);
}

void GameObjectManager::Update(float delta_time, float beat_time)
{
    for (auto gameObject : gameObjects_)
    {
        gameObject->Update(delta_time, beat_time);
    }
}

void GameObjectManager::DelayedUpdate(float delta_time, float beat_time)
{
    for (auto gameObject : gameObjects_)
    {
        gameObject->DelayedUpdate(delta_time, beat_time);
    }
}

void GameObjectManager::Draw() const
{
    for (auto gameObject : gameObjects_)
    {
        gameObject->Draw();
    }
}

void GameObjectManager::DelayedDraw() const
{
    for (auto gameObject : gameObjects_)
    {
        gameObject->DelayedDraw();
    }
}

void GameObjectManager::Collision()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = next(i); j != gameObjects_.end(); j++)
        {
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnCollision(**j);
        }
    }
}

void GameObjectManager::ReverseCollision()
{
    for (auto i = --gameObjects_.end(); i != --gameObjects_.begin(); i--)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = prev(i); j != --gameObjects_.begin(); j--)
        {
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnCollision(**j);
        }
    }
}

void GameObjectManager::OneWayCollision()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = gameObjects_.begin(); j != gameObjects_.end(); j++)
        {
            if (i == j) continue;
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnOneWayCollision(**j);
        }
    }
}

void GameObjectManager::OneWayReverseCollision()
{
    for (auto i = --gameObjects_.end(); i != --gameObjects_.begin(); i--)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = --gameObjects_.end(); j != --gameObjects_.begin(); j--)
        {
            if (i == j) continue;
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnOneWayCollision(**j);
        }
    }
}

void GameObjectManager::Interaction()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = next(i); j != gameObjects_.end(); j++)
        {
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnCollision(**j);
            else (*i)->OnMissedCollision(**j);
        }
    }
}


void GameObjectManager::ReverseInteraction()
{
    for (auto i = --gameObjects_.end(); i != --gameObjects_.begin(); i--)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = prev(i); j != --gameObjects_.begin(); j--)
        {
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnCollision(**j);
            else (*i)->OnMissedCollision(**j);
        }
    }
}

void GameObjectManager::OneWayInteraction()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = gameObjects_.begin(); j != gameObjects_.end(); j++)
        {
            if (i == j) continue;
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnOneWayCollision(**j);
            else (*i)->OnMissedOneWayCollision(**j);
        }
    }
}

void GameObjectManager::OneWayReverseInteraction()
{
    for (auto i = --gameObjects_.end(); i != --gameObjects_.begin(); i--)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = --gameObjects_.end(); j != --gameObjects_.begin(); j--)
        {
            if (i == j) continue;
            if (!(*j)->GetActive()) continue;
            if ((*i)->IsCollision(**j)) (*i)->OnOneWayCollision(**j);
            else (*i)->OnMissedOneWayCollision(**j);
        }
    }
}

void GameObjectManager::Perception()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if (!(*i)->GetActive()) continue;
        for (auto j = gameObjects_.begin(); j != gameObjects_.end(); j++)
        {
            if (i == j) continue;
            if (!(*j)->GetActive()) continue;
            if ((*i)->Perception(**j)) (*i)->InRange(**j);
            else (*i)->NotInRange(**j);
        }
    }
}

void GameObjectManager::Remove()
{
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); )
    {
        if ((*i)->IsDead())
        {
            delete *i;
            i = gameObjects_.erase(i);
        }
        else i++;
    }
}

GameObject* GameObjectManager::Find(const std::string& string, const bool byTag) const
{
    for (auto gameObject : gameObjects_)
    {
        if (byTag && gameObject->GetTag() == string) return gameObject;
        else if (!byTag && gameObject->GetName() == string) return gameObject;
    }
    return nullptr;
}

GameObject* GameObjectManager::Find(const int ID) const
{
    for (auto gameObject : gameObjects_)
    {
        if (gameObject->GetID() == ID)
        {
            return gameObject;
        }
    }
    return nullptr;
}

void GameObjectManager::ChangeListOrder(const std::string& name, const std::string& newPos)
{
    std::list<GameObject*>::iterator gameObjectPos;
    for (auto i = gameObjects_.begin(); i != gameObjects_.end(); i++)
    {
        if ((*i)->GetName() == name) gameObjectPos = i;
    }

    if (newPos == "begin") ChangeListOrder(gameObjectPos, gameObjects_.begin());
    else ChangeListOrder(gameObjectPos, gameObjects_.end());
}

void GameObjectManager::ChangeListOrder(std::list<GameObject*>::iterator posInList, std::list<GameObject*>::iterator newPosInList)
{
    gameObjects_.splice(newPosInList, gameObjects_, posInList);
}

void GameObjectManager::Clear()
{
    for (auto gameObject : gameObjects_)
    {
        delete gameObject;
    }
    gameObjects_.clear();
}