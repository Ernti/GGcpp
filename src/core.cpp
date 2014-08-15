#include "core.h"

Core::Core()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDLNet_Init();

    events = new Events();
    renderer = new Renderer();
    movement = new Movement();

    player = new Player(movement);
    renderer->addPlayer(player);
    events->addPlayer(player);
    renderer->addRenderObject(player->getSs());

    Spaceship* spaceship = new Spaceship(100., 000.);
    renderer->addRenderObject(spaceship);

    GameVariables::running = true;
    //TODO: check for successful initialization
}

Core::~Core()
{
    delete player;
    delete movement;
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
        movement->loop();
        renderer->render();
    }
}
