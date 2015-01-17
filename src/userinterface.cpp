#include "userinterface.h"

UserInterface::UserInterface(SDL_Renderer* screenin)
{
    screen = screenin;
    font = TTF_OpenFont("gfx/fonts/arial.ttf", 16);
}

UserInterface::~UserInterface()
{
    TTF_CloseFont(font);
}

void UserInterface::render()
{
    renderChat();
    //renderWindows();
}

void UserInterface::renderChat()
{
    int chatsize = GameVariables::chat.size();
    for(int it = 0; it < chatsize; it++)
    {
        if(it >= chatsize - 5)
        {
            SDL_Color color={255,255,255};
            SDL_Surface *text_surface;
            char chatchar[16];
            strncpy(chatchar, GameVariables::chat[it].c_str(), sizeof(chatchar));
            if(!(text_surface=TTF_RenderText_Solid(font,chatchar,color)))
            {
                std::cout << TTF_GetError() << std::endl;
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
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
        }
    }
}

void UserInterface::renderWindows()
{
    for(unsigned int i = 0; i < windows.size(); i++)
    {
        SDL_SetRenderDrawColor(screen, 50, 50, 50, 255);
        SDL_RenderDrawRect(screen, windows[i]->getRect());
        for(unsigned int j = 0; j < windows[i]->boxes.size(); j++)
        {
            SDL_SetRenderDrawColor(screen, 100, 100, 100, 255);
            SDL_Rect* rect;
            rect->x = windows[i]->boxes[j]->getRect()->x + windows[i]->getRect()->x;
            rect->y = windows[i]->boxes[j]->getRect()->y + windows[i]->getRect()->y;
            rect->w = windows[i]->boxes[j]->getRect()->w;
            rect->h = windows[i]->boxes[j]->getRect()->h;
            SDL_RenderDrawRect(screen, rect);
            for(unsigned int k = 0; k < windows[i]->boxes[j]->texts.size(); j++)
            {
                SDL_Color color={255,255,255};
                SDL_Surface *text_surface;
                char textline[16];
                strncpy(textline, "test", sizeof(textline));
                if(!(text_surface=TTF_RenderText_Solid(font,textline,color)))
                {
                    std::cout << TTF_GetError() << std::endl;
                }
                else
                {
                    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(screen, text_surface);
                    int w, h;
                    SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);

                    SDL_Rect* rect;
                    rect->x = windows[i]->boxes[j]->getRect()->x + windows[i]->boxes[j]->texts[k]->getRect()->x + windows[i]->getRect()->x;
                    rect->y = windows[i]->boxes[j]->getRect()->y + windows[i]->boxes[j]->texts[k]->getRect()->y + windows[i]->getRect()->y;
                    rect->w = windows[i]->boxes[j]->texts[k]->getRect()->w;
                    rect->h = windows[i]->boxes[j]->texts[k]->getRect()->h;

                    SDL_RenderCopy(screen, text_texture, NULL, rect);
                    SDL_FreeSurface(text_surface);
                    SDL_DestroyTexture(text_texture);
                }
            }
            /*for(unsigned int l = 0; l < windows[i]->boxes[j]->buttons.size(); j++)
            {
                SDL_SetRenderDrawColor(screen, 30, 30, 30, 255);
                SDL_RenderDrawRect(screen, windows[i]->boxes[j]->buttons[l]->getRect());
                SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
            }*/
            SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
        }
        SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
    }
}
