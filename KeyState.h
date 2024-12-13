#ifndef INCLUDE_KEYSTATE_H
#define INCLUDE_KEYSTATE_H
struct KeyState
{
    char key;
    bool pressed;
    int timesPressed;
};
#endif //INCLUDE_KEYSTATE_H