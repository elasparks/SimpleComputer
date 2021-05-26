#include "../../include/MyReadKey.h"
/**
 * Switch display symbols which u put in the terminal
 * @file TermEcho.cpp
 * @return Operation result
 */
int MyReadKey::switchEcho()
{
    termios thisSettings{};
    if (tcgetattr(0, &thisSettings) != 0) {
        return -1; // if you can't read the settings for the terminal
    }
    thisSettings.c_lflag ^= ECHO;
    if (tcsetattr(0, TCSANOW, &thisSettings) != 0) {
        return -1; // if it failed to set new settings for the terminal
    }
    return 0;
}