#include "KeyState.h"
#include "gestordeprogreso.h"
#include <windows.h>
#include <iostream>
using namespace std;

 KeyState keyState[4]{
    {'W', false, 0},
    {'A', false, 0},
    {'S', false, 0},
    {'D', false, 0}};

int main()
{
    ProgressController* progressController = new ProgressController();
    bool showResults = false;
    constexpr int cyclesPerSecond = 60;
    constexpr float msWait = 1000/cyclesPerSecond;
    constexpr int autoSaveTime = cyclesPerSecond * 15;
    unsigned short iterations = 0, afkIterations = 0;
    size_t second = 0;
    cout << "Press CTRL, SHIFT and C to manually save to drive. This features autosave every " << autoSaveTime << " seconds.\n";
    while (true){
        Sleep(msWait);
        iterations++;
        bool somethingPressed = false;
        for (size_t i = 0; i < 4 ; i++) {
            const bool isDown = GetAsyncKeyState(keyState[i].key) & 0x8000;
            if (!isDown) {
                keyState[i].pressed = false;
                continue;
            }
            if (isDown && !keyState[i].pressed) {
                cout << keyState[i].key;
                keyState[i].timesPressed++;
                keyState[i].pressed = true, somethingPressed = true;
            }
        }
        const bool isCtrlShiftCDown = (GetAsyncKeyState(VK_LCONTROL) & 0x8000) && (GetAsyncKeyState(VK_LSHIFT) & 0x8000) && (GetAsyncKeyState('C') & 0x8000);
        !(somethingPressed || isCtrlShiftCDown) ? afkIterations++ : afkIterations = 0; //check if afk
        if (afkIterations >= cyclesPerSecond * 5) { 
            cout << "afk!\n"; //debug only
        }
        while (afkIterations >=  cyclesPerSecond * 5) {
        //TODO: add condition to check if any game .exe isn't running
            Sleep(200);
            bool somethingPressed = false;
            for (unsigned short i = 0; i < 4; i++) {
                somethingPressed = GetAsyncKeyState(keyState[i].key) & 0x8000;
                if (somethingPressed) {
                    afkIterations = 0;
                    break;
                }
            }
        }
        progressController->bufferProgress(keyState);
        if (iterations == cyclesPerSecond) {
            iterations = 0;
            second++;
            cout <<"\n" << second << " ";
            if (second == autoSaveTime)
            {
                cout << "\nautosave!\n";
                progressController->saveProgress(keyState);
            }
        }
        
        if (!isCtrlShiftCDown) {
            showResults = false;
            continue;
        }
        if (isCtrlShiftCDown && !showResults) {
            progressController->saveProgress(keyState);
            showResults = true;
        }
    }
}