#pragma once

#include "Tags.h"
#include "Events.h"

class GameObject;

class GameObjectManager
{
public:
    static void Init();
    static void Release();
    static void Update(const float deltaTime);
    static void Render(const HDC hdc);

    static void RegisterGameObject(GameObject* go);
    static void DestroyGameObject(const int goId);
    static GameObject* FindWithTag(const Kind tag);
    static vector<GameObject*> FindGameObjectsWithTag(const Kind tag);

    static void Publish(const Event event);

private:
    static int gameObjectId;
    static vector<GameObject*> gameObjects;
    static map<Event, vector<GameObject*>> events;
};
