#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"

int GameObjectManager::gameObjectId = 0;
vector<GameObject*> GameObjectManager::gameObjects;
map<Event, vector<GameObject*>> GameObjectManager::events;

void GameObjectManager::Init()
{
    for (auto& go : gameObjects)
    {
        go->InitRec();
    }
}

void GameObjectManager::Release()
{
    for (auto& go : gameObjects)
    {
        go->ReleaseRec();
    }
}

void GameObjectManager::Update(const float deltaTime)
{
    for (auto& go : gameObjects)
    {
        go->UpdateRec(deltaTime);
    }
}

void GameObjectManager::Render(const HDC hdc)
{
    for (auto& go : gameObjects)
    {
        go->RenderRec(hdc);
    }
}

void GameObjectManager::RegisterGameObject(GameObject* go)
{
    go->Id(gameObjectId++);

    for (auto event : go->SubscribedEvents())
    {
        events[event].push_back(go);
    }

    gameObjects.push_back(go);
}

void GameObjectManager::DestroyGameObject(const int goId)
{
    for (auto it = gameObjects.begin(); it != gameObjects.end();)
    {
        if ((*it)->Id() == goId)
        {
            gameObjects.erase(it);
            return;
        }
        else
        {
            ++it;
        }
    }
}

GameObject* GameObjectManager::FindWithTag(const Kind tag)
{
    for (auto& go : gameObjects)
    {
        if (go->Tag() == tag)
        {
            return go;
        }
    }

    return nullptr;
}

vector<GameObject*> GameObjectManager::FindGameObjectsWithTag(const Kind tag)
{
    vector<GameObject*> gos;
    for (auto& go : gameObjects)
    {
        if (go->Tag() == tag)
        {
            gos.push_back(go);
        }
    }

    return gos;
}

void GameObjectManager::Publish(const Event event)
{
    for (auto& go : events[event])
    {
        go->ExecuteEvent(event);
    }
}
