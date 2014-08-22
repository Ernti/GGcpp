#include "gamevariables.h"

bool GameVariables::running = false;
int GameVariables::screenResX = 1280;
int GameVariables::screenResY = 720;
std::vector<std::string> GameVariables::chat;
std::string GameVariables::chatmessage = "";
std::string GameVariables::chatinput = "";
bool GameVariables::chatActive = false;


std::string GameVariables::getChatmessage()
{
    std::string output = chatmessage;
    chatmessage.clear();
    return output;
}

void GameVariables::setChatmessage()
{
    chatmessage = chatinput;
    chatinput.clear();
}
