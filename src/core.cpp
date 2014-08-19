#include "core.h"

Core::Core()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDLNet_Init();

    Packet * packet = new Packet();
    network = new Network(packet);

    events = new Events(&network->broadcastlist, &network->receivelist);
    renderer = new Renderer();
    movement = new Movement();

    player = new Player(movement, packet, &network->broadcastlist);
    renderer->addPlayer(player);
    events->addPlayer(player);
    renderer->addRenderObject(player->getSs());

    Spaceship* spaceship = new Spaceship(100., 000.);
    renderer->addRenderObject(spaceship);

    //delete packet;

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
        if(network->running)
        {
            network->loop();
        }
        events->eventLoop();
        movement->loop();
        renderer->render();
    }
}
