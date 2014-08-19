#include "network.h"

Network::Network(Packet * returnPacket)
{
    IPaddress ip;
    //TCPsocket tcpsock;

    if(SDLNet_ResolveHost(&ip,"localhost",2000)==-1) {
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

        receiverthread = thread(receiver, this);
        senderthread = thread(sender, this);
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
            std::cout << "receiver: " << numready << std::endl;
            std::cout << "SDLNet_CheckSockets: success!" << std::endl;
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
                    std::cout << packet->chat << std::endl;
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

            std::cout << packet->chat << std::endl;

            result=SDLNet_TCP_Send(socket, packet, sizeof(Packet));
            if(result<sizeof(packet)) {
                printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                running = false;
            }
            broadcastlist.erase(broadcastlist.begin());
        }
    }
}

void Network::loop()
{
    if(Network::running)
    {
        while(!receivelist.empty())
        {
            receivelist.erase(receivelist.begin());
        }
    }
    else
    {
        std::cout << "disconnected!" << std::endl;
        //GameVariables::running = 0;
    }
}
