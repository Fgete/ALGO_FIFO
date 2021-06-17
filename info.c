#include "info.h"

// FPS DEBUG
void FPS_Info(){
    // We get an average frame rate at 24fps.
    // Enough to make animations but still too low for a full game.
    nFrame++;
    // printf("nFrame : %d\n", nFrame);
    if (oldClock != (int)(clock() / 1000)){
        fps = nFrame;
        nFrame = 0;
        oldClock = (int)(clock() / 1000);
        printf("time = %ds | FPS = %d\n", oldClock, fps);
    }
}
