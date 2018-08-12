#include "stdafx.h"
#include "GameObject.h"
#include "image.h"

GameObject::GameObject() :
    _id(-1),
    _tag(Kind::kIdleKind),
    _parent(nullptr),
    _rect(RECT()),
    _mainGame(nullptr),
    _pos(RECT())
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Update(const float deltaTime)
{
}

void GameObject::Render(const HDC hdc)
{
    for (auto& image : _images)
    {
        image->render(hdc, _rect.left, _rect.top);
    }
}

void GameObject::Render(const HDC hdc, const int index)
{
    if (_images.size() > index)
    {
        _images.at(index)->render(hdc, _rect.left, _rect.top);
    }
}

void GameObject::Render(const HDC hdc, const int index, BYTE alpha)
{
    if (_images.size() > index)
    {
        _images.at(index)->render(hdc, _rect.left, _rect.top, alpha);
    }
}

void GameObject::InitRec()
{
    Init();

    for (auto& child : _children)
    {
        child->InitRec();
    }
}

void GameObject::ReleaseRec()
{
    for (auto& child : _children)
    {
        child->ReleaseRec();
    }

    Release();
}

void GameObject::UpdateRec(const float deltaTime)
{
    Update(deltaTime);

    for (auto& child : _children)
    {
        child->UpdateRec(deltaTime);
    }
}

void GameObject::RenderRec(const HDC hdc)
{
    Render(hdc);

    for (auto& child : _children)
    {
        child->RenderRec(hdc);
    }
}

void GameObject::Id(const int id)
{
    _id = id;
}

void GameObject::Tag(const Kind tag)
{
    _tag = tag;
}

Kind GameObject::Tag() const
{
    return _tag;
}

void GameObject::Subscribe(const Event event)
{
    _events.push_back(event);
}

vector<Event> GameObject::SubscribedEvents()
{
    return _events;
}

void GameObject::ExecuteEvent(const Event event)
{
}

int GameObject::Id() const
{
    return _id;
}

void GameObject::Rect(const RECT rect)
{
    this->_rect = rect;
}

void GameObject::Rect(const int left, const int top, const int right, const int bottom)
{
    this->_rect = RECT { left, top, right, bottom };
}

RECT GameObject::Rect() const
{
    return _rect;
}

void GameObject::Velocity(const Vector2 vec2)
{
    _velocity = vec2;

    for (auto& child : _children)
    {
        child->Velocity(_velocity);
    }
}

void GameObject::Velocity(const float x, const float y)
{
    _velocity.x = x;
    _velocity.y = y;

    for (auto& child : _children)
    {
        child->Velocity(_velocity);
    }
}

Vector2 GameObject::Velocity() const
{
    return _velocity;
}

void GameObject::VelocityX(float x)
{
    _velocity.x = x;

    for (auto& child : _children)
    {
        child->VelocityX(_velocity.x);
    }
}

float GameObject::VelocityX() const
{
    return _velocity.x;
}

void GameObject::VelocityY(float y)
{
    _velocity.y = y;

    for (auto& child : _children)
    {
        child->VelocityY(_velocity.y);
    }
}

float GameObject::VelocityY() const
{
    return _velocity.y;
}

void GameObject::Move()
{
    _rect.left += static_cast<LONG>(_velocity.x);
    _rect.right += static_cast<LONG>(_velocity.x);
    _rect.top += static_cast<LONG>(_velocity.y);
    _rect.bottom += static_cast<LONG>(_velocity.y);

    for (auto& child : _children)
    {
        child->Move();
    }
}

void GameObject::SetParent(GameObject* parent)
{
    this->_parent = parent;
}

GameObject* GameObject::GetParent() const
{
    return _parent;
}

void GameObject::SetChild(GameObject* child)
{
    if (_mainGame != nullptr)
    {
        child->SetScene(_mainGame);
    }

    child->SetParent(this);
    _children.push_back(child);
}

void GameObject::RegisterImage(image* image)
{
    _images.push_back(image);
}

vector<image*> GameObject::Images()
{
    return _images;
}

void GameObject::SetScene(mainGame* mg)
{
    _mainGame = mg;
}

void GameObject::Position(const int x, const int y, const int width, const int height)
{
    _pos.left = x;
    _pos.top = y;
    _pos.right = width;
    _pos.bottom = height;
}

RECT GameObject::Position() const
{
    return _pos;
}
