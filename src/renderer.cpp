#include "renderer.h"

Renderer::Renderer()
{
    window = SDL_CreateWindow("GG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GameVariables::screenResX, GameVariables::screenResY, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    screen = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    screenShiftX = GameVariables::screenResX / 2;
    screenShiftY = GameVariables::screenResY / 2;

    texturizer = new Texturizer(screen);

    font = TTF_OpenFont("gfx/fonts/arial.ttf", 16);
}

Renderer::~Renderer()
{
    TTF_CloseFont(font);
}

void Renderer::addPlayer(Player* playerin)
{
    player = playerin;
}

void Renderer::addRenderObject(Renderable* renderable)
{
    renderlist.push_back(renderable);
}

void Renderer::render()
{
    SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
    SDL_RenderClear(screen);

    //render stuff


    float lastx = player->getSs()->getX();
    float lasty = player->getSs()->getY();

    for(unsigned int it = 0;it<player->getTargets();it++)
    {
        if(player->getTargetX(it) - player->getSs()->getX() > 1 || player->getTargetX(it) - player->getSs()->getX() < -1
           || player->getTargetY(it) - player->getSs()->getY() > 1|| player->getTargetY(it) - player->getSs()->getY() < -1)
        {
            SDL_SetRenderDrawColor(screen, 0, 255, 0, 255);
            SDL_RenderDrawLine(screen,
                               ((lastx - player->getX()) / player->getZ() + screenShiftX), ((lasty - player->getY()) / player->getZ() + screenShiftY),
                               ((player->getTargetX(it) - player->getX()) / player->getZ() + screenShiftX), ((player->getTargetY(it) - player->getY()) / player->getZ() + screenShiftY));
            SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
            lastx = player->getTargetX(it);
            lasty = player->getTargetY(it);
        }
    }

    for(unsigned int it = 0;it<renderlist.size();it++)
    {
        Renderable* renderable = renderlist[it];
        SDL_Point center;

        SDL_Rect posrect;
        posrect.w = 128 / player->getZ();
        posrect.h = 128 / player->getZ();
        posrect.x = (renderable->getX() - player->getX()) / player->getZ() + screenShiftX - (posrect.w / 2);
        posrect.y = (renderable->getY() - player->getY()) / player->getZ() + screenShiftY - (posrect.h / 2);
        center.x = 64 / player->getZ();
        center.y = 64 / player->getZ();

        SDL_RenderCopyEx(screen, texturizer->loadTexture(renderable->getTex()), NULL, &posrect, renderable->getR(), &center, SDL_FLIP_NONE);
    }
    /*
    Renderable* renderable = player->getSs();
    SDL_Point center;

    SDL_Rect posrect;
    posrect.w = 128 / player->getZ();
    posrect.h = 128 / player->getZ();
    posrect.x = (renderable->getX() - player->getX()) / player->getZ() + screenShiftX - (posrect.w / 2);
    posrect.y = (renderable->getY() - player->getY()) / player->getZ() + screenShiftY - (posrect.h / 2);
    center.x = 64;
    center.y = 64;

    SDL_RenderCopyEx(screen, texturizer->loadTexture(renderable->getTex()), NULL, &posrect, renderable->getR(), &center, SDL_FLIP_NONE);
    */

    int chatsize = GameVariables::chat.size();
    for(int it = 0; it < chatsize; it++)
    {
        if(it > chatsize - 5)
        {
            SDL_Color color={255,255,255};
            SDL_Surface *text_surface;
            char chatchar[16];
            strncpy(chatchar, GameVariables::chat[it].c_str(), sizeof(chatchar));
            if(!(text_surface=TTF_RenderText_Solid(font,chatchar,color)))
            {
                std::cout << TTF_GetError() << std::endl;
            //handle error here, perhaps print TTF_GetError at least
            }
            else
            {
                SDL_Texture * text_texture = SDL_CreateTextureFromSurface(screen, text_surface);
                int w, h;
                SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);

                SDL_Rect chatrect;
                chatrect.x = 10;
                chatrect.y = GameVariables::screenResY - 30 - (chatsize - it) * h;
                chatrect.h = h;
                chatrect.w = w;

                SDL_RenderCopy(screen, text_texture, NULL, &chatrect);
                //perhaps we can reuse it, but I assume not for simplicity.
                SDL_FreeSurface(text_surface);
                SDL_DestroyTexture(text_texture);
            }
        }
    }

    if(GameVariables::chatinput.size() > 0)
    {
        SDL_Color color={255,255,255};
        SDL_Surface *text_surface;
        char chatchar[16];
        strncpy(chatchar, GameVariables::chatinput.c_str(), sizeof(chatchar));
        if(!(text_surface=TTF_RenderText_Solid(font,chatchar,color)))
        {
            std::cout << TTF_GetError() << std::endl;
        //handle error here, perhaps print TTF_GetError at least
        }
        else
        {
            SDL_Texture * text_texture = SDL_CreateTextureFromSurface(screen, text_surface);
            int w, h;
            SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);

            SDL_Rect chatrect;
            chatrect.x = 10;
            chatrect.y = GameVariables::screenResY - 30;
            chatrect.h = h;
            chatrect.w = w;

            SDL_RenderCopy(screen, text_texture, NULL, &chatrect);
            //perhaps we can reuse it, but I assume not for simplicity.
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
        }
    }

    if(GameVariables::chatActive)
    {
        if(SDL_GetTicks() > chatblinktick + 500)
        {
            if(chatblink)
            {
                chatblink = false;
            }
            else
            {
                chatblink = true;
            }
            chatblinktick = SDL_GetTicks();
        }
        SDL_Color color;
        if(chatblink)
        {
            color={0,0,0};
        }
        else
        {
            color={255,255,255};
        }
        SDL_Surface *text_surface;
        if(!(text_surface=TTF_RenderText_Solid(font,"|",color)))
        {
            std::cout << TTF_GetError() << std::endl;
        //handle error here, perhaps print TTF_GetError at least
        }
        else
        {
            SDL_Texture * text_texture = SDL_CreateTextureFromSurface(screen, text_surface);
            int w, h, chatw, chath;
            char chatchar[16];
            strncpy(chatchar, GameVariables::chatinput.c_str(), sizeof(chatchar));
            TTF_SizeText(font, chatchar, &chatw, &chath);
            SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);

            SDL_Rect chatrect;
            chatrect.x = 10 + chatw;
            chatrect.y = GameVariables::screenResY - 30;
            chatrect.h = h;
            chatrect.w = w;

            SDL_RenderCopy(screen, text_texture, NULL, &chatrect);
            //perhaps we can reuse it, but I assume not for simplicity.
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
        }
    }

    SDL_RenderPresent(screen);
}
