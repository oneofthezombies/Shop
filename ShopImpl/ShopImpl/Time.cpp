#include "stdafx.h"
#include "Time.h"

chrono::time_point<chrono::system_clock> Time::startTime = chrono::system_clock::time_point();
chrono::time_point<chrono::system_clock> Time::previousTime = chrono::system_clock::time_point();
float Time::deltaTime = 0.0f;

void Time::Init()
{
    startTime = chrono::system_clock::now();
    previousTime = chrono::system_clock::now();
    deltaTime = 0.0f;
}

void Time::Update()
{
    auto currentTime = chrono::system_clock::now();
    chrono::duration<float> dt = currentTime - previousTime;
    deltaTime = dt.count();
    previousTime = currentTime;
}

float Time::DeltaTime()
{
    return deltaTime;
}
