#include "core.h"

Core::Core()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    SDLNet_Init();

    Packet * packet = new Packet();
    network = new Network(packet);

    events = new Events();
    renderer = new Renderer();
    movement = new Movement();

    player = new Player(movement, packet);
    renderer->addPlayer(player);
    events->addPlayer(player);
    //renderer->addRenderObject(player->getSs());

    //delete packet;

    network->start(movement, renderer, player);

    GameVariables::running = true;
    //TODO: check for successful initialization
}

Core::~Core()
{
    delete network;
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
        network->loop();
        events->eventLoop();
        movement->loop();
        renderer->render();
    }
}
