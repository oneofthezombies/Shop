#pragma once

class Time
{
public:
    static void Init();
    static void Update();

    static float DeltaTime();

private:
    static chrono::time_point<chrono::system_clock> startTime;
    static chrono::time_point<chrono::system_clock> previousTime;
    static float deltaTime;
};

