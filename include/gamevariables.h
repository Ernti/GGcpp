#ifndef GAMEVARIABLES_H
#define GAMEVARIABLES_H

#include <string>
#include <vector>

class GameVariables
{
    public:
        static bool running;
        static int screenResX;
        static int screenResY;
        static std::vector<std::string> chat;
        static std::string chatinput;
        static std::string getChatmessage();
        static void setChatmessage();
        static bool chatActive;
    protected:
    private:
        static std::string chatmessage;
};

#endif // GAMEVARIABLES_H
