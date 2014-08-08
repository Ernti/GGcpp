#include "core.h"

Core::Core()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDLNet_Init();

    events = new Events();
    renderer = new Renderer();

    player = new Player();
    renderer->addPlayer(player);

    GameVariables::running = true;
    //TODO: check for successful initialization
}

Core::~Core()
{
    delete renderer;
    delete events;
    IMG_Quit();
    SDL_Quit();
}

void Core::loop()
{
    while(GameVariables::running)
    {
        events->eventLoop();
        renderer->render();
    }
}
