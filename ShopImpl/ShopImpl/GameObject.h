#pragma once

#include "Tags.h"
#include "Constants.h"
#include "Events.h"

class image;

struct Vector2
{
    Vector2() : x(0.0f), y(0.0f) {}
    virtual ~Vector2() {}

    float x;
    float y;
};

class mainGame;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void Init();
    virtual void Release();
    virtual void Update(const float deltaTime);
    virtual void Render(const HDC hdc);
    virtual void Render(const HDC hdc, const int index);
    virtual void Render(const HDC hdc, const int index, BYTE alpha);

    virtual void InitRec() final;
    virtual void ReleaseRec() final;
    virtual void UpdateRec(const float deltaTime) final;
    virtual void RenderRec(const HDC hdc) final;

    virtual void Id(const int id) final;
    virtual int Id() const final;

    virtual void Tag(const Kind tag) final;
    virtual Kind Tag() const final;

    virtual void Subscribe(const Event event) final;
    virtual vector<Event> SubscribedEvents() final;
    virtual void ExecuteEvent(const Event event);

    virtual void Rect(const RECT rect) final;
    virtual void Rect(const int left, const int top, const int right, const int bottom) final;
    virtual RECT Rect() const final;

    virtual void Velocity(const Vector2 vec2) final;
    virtual void Velocity(const float x, const float y)final;
    virtual Vector2 Velocity() const final;
    virtual void VelocityX(const float x) final;
    virtual float VelocityX() const final;
    virtual void VelocityY(const float y) final;
    virtual float VelocityY() const final;
    virtual void Move() final;

    virtual void SetParent(GameObject* parent) final;
    virtual GameObject* GetParent() const final;
    virtual void SetChild(GameObject* child) final;

    virtual void RegisterImage(image* image) final;
    virtual vector<image*> Images() final;

    virtual void SetScene(mainGame* mg) final;

    virtual void Position(const int x, const int y, const int width, const int height) final;
    virtual RECT Position() const final;

protected:
    int _id;
    Kind _tag;
    vector<Event> _events;

    RECT _rect;
    RECT _pos;
    Vector2 _velocity;

    vector<image*> _images;

    GameObject* _parent;
    vector<GameObject*> _children;

    mainGame* _mainGame;
};
