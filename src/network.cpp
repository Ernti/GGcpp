#include "network.h"

Network::Network(Packet * returnPacket)
{
    IPaddress ip;
    //TCPsocket tcpsock;

    if(SDLNet_ResolveHost(&ip,"gg-game.net",2000)==-1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        //exit(1);
    }

    socket=SDLNet_TCP_Open(&ip);
    if(!socket) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        //exit(2);
    }
    else
    {
        //Login username and password
        sockets=SDLNet_AllocSocketSet(1);
        SDLNet_TCP_AddSocket(sockets,socket);

        int numready;

        numready=SDLNet_CheckSockets(sockets, 10000);
        if(numready==-1)
        {
            std::cout << "receiver error" << std::endl;
            std::cout << "SDLNet_CheckSockets: " << SDLNet_GetError() << std::endl;
            running = false;
        }
        else if(numready)
        {
            std::cout << "receiver: " << numready << std::endl;
            std::cout << "SDLNet_CheckSockets: success!" << std::endl;
            if(SDLNet_SocketReady(socket)!=0)
            {
                int result;

                result=SDLNet_TCP_Recv(socket, returnPacket, sizeof(Packet));
                if(result<=0) {
                    running = false;
                }
                else
                {
                    std::cout << "test!" << std::endl;
                    if(strcmp(returnPacket->chat, "connected") == 0)
                    {
                        id = returnPacket->id;
                        std::cout << "connected!" << std::endl;
                        running = true;
                    }
                }
            }
            else
            {
                running = false;
            }
        }

        receiverthread = thread(&Network::receiver, this);
        senderthread = thread(&Network::sender, this);
    }
}

Network::~Network()
{
    running = false;
    if(receiverthread.joinable())
    {
        receiverthread.join();
    }
    if(senderthread.joinable())
    {
        senderthread.join();
    }
    SDLNet_TCP_Close(socket);
    SDLNet_Quit();
    cout << "net closed!" << endl;
}

void Network::receiver()
{
    while(Network::running)
    {
        int numready;

        numready=SDLNet_CheckSockets(sockets, 1000);
        if(numready==-1)
        {
            std::cout << "receiver error" << std::endl;
            std::cout << "SDLNet_CheckSockets: " << SDLNet_GetError() << std::endl;
            running = false;
        }
        else if(numready)
        {
            if(SDLNet_SocketReady(socket)!=0)
            {
                int result;
                Packet * packet = new Packet();

                result=SDLNet_TCP_Recv(socket, packet, sizeof(Packet));
                if(result<=0) {
                    running = false;
                }
                else
                {
                    receivelist.push_back(packet);
                }
            }
            else
            {
                running = false;
            }
        }
    }
}

void Network::sender()
{
    while(running)
    {
        while(!broadcastlist.empty())
        {
            unsigned int result;

            Packet * packet = new Packet();
            packet = broadcastlist.front();

            result=SDLNet_TCP_Send(socket, packet, sizeof(Packet));
            if(result<sizeof(packet)) {
                printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                running = false;
            }
            broadcastlist.erase(broadcastlist.begin());
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(10));
    }
}

void Network::start(Movement* movementin, Renderer* rendererin, Player* playerin)
{
    movement = movementin;
    renderer = rendererin;
    player = playerin;
    spaceschips.push_back(player->getSs());
    renderer->addRenderObject(player->getSs());
}

void Network::loop()
{
    if(Network::running)
    {
        /*
        for(unsigned int i = 0;i<spaceschips.size();i++)
        {
            bool changes = false;
            Packet * packet = new Packet();
            if(subscription[i]->getSs()->getX() != reference[i].getSs()->getX())
            {
                packet->x = subscription[i]->getSs()->getX();
                changes = true;
            }
            if(subscription[i]->getSs()->getY() != reference[i].getSs()->getY())
            {
                packet->y = subscription[i]->getSs()->getY();
                changes = true;
            }

            if(changes)
            {
                broadcastlist.push_back(packet);
                reference[i] = *subscription[i];
            }
        }*/

        nowtick = SDL_GetTicks();
        if(nowtick - lasttick > 100)
        {
            Packet* packet = new Packet();
            strncpy(packet->chat, GameVariables::getChatmessage().c_str(), sizeof(packet->chat));
            packet->id = player->getSs()->getId();
            packet->x = player->getSs()->getX();
            packet->y = player->getSs()->getY();
            packet->targetX = player->getTargetX();
            packet->targetY = player->getTargetY();
            broadcastlist.push_back(packet);
            lasttick = nowtick;
        }



        while(!receivelist.empty())
        {
            std::string chattmp = receivelist.front()->chat;
            if(chattmp.size() > 0)
            {
                std::string chatline = "";
                chatline.append(": ");
                chatline.append(chattmp);
                GameVariables::chat.push_back(chatline);
            }
            bool newship = true;
            for(unsigned int i = 0;i<spaceschips.size();i++)
            {
                if(receivelist.front()->id == spaceschips[i]->getId())
                {
                    newship = false;
                    int xdif = spaceschips[i]->getTargetX() - receivelist.front()->targetX;
                    int ydif = spaceschips[i]->getTargetY() - receivelist.front()->targetY;
                    if(xdif > 1 || xdif < -1 || ydif > 1 || ydif < -1)
                    {
                        spaceschips[i]->setTarget(receivelist.front()->targetX, receivelist.front()->targetY);
                        movement->subscribe(std::bind(&Spaceship::move, spaceschips[i]));
                    }
                }
            }
            if(newship)
            {
                Spaceship * spaceship = new Spaceship(receivelist.front()->x, receivelist.front()->y, receivelist.front()->id);
                spaceship->setTarget(receivelist.front()->targetX, receivelist.front()->targetY);
                spaceschips.push_back(spaceship);
                renderer->addRenderObject(spaceship);
                movement->subscribe(std::bind(&Spaceship::move, spaceship));
            }
            receivelist.erase(receivelist.begin());
        }
    }
    else
    {
        std::cout << "disconnected!" << std::endl;
        //GameVariables::running = 0;
    }
}
