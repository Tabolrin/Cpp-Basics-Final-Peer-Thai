#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

// Simulated game update function
void Update(float deltaTime) 
{
    // Game logic here
    cout << "Updating game logic. Delta Time: " << deltaTime << " seconds" << endl;
}

// Simulated render function
void Render() 
{
    // Rendering code here
    cout << "Rendering frame" << endl;
}

// Dedicated game loop function
void RunGameLoop() 
{
    using namespace std::chrono;

    auto lastTime = high_resolution_clock::now();
    float timeAccumulator = 0.0f;

    const float updateInterval = 1.0f; // seconds
    bool running = true;

    while (running) 
    {
        auto currentTime = high_resolution_clock::now();
        float deltaTime = duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        timeAccumulator += deltaTime;

        if (timeAccumulator >= updateInterval)
        {
            Update(timeAccumulator); // or pass 1.0f
            Render();
            timeAccumulator = 0.0f;
        }

        // prevent CPU burn — optional
        std::this_thread::sleep_for(milliseconds(1));

        if (int x  = 1) running = false;
    }
}
