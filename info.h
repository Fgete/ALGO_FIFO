#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED

// ------ GAME INFO ------
// Const
#define TITLE_LENGTH 16
#define SRC_LENGTH 32
#define N_OBJ_COLLECTION 16
// Title
#define GAME_TITLE "GAME NAME"
// Credits
#define DEV_NAME0 "François GETE"
#define DEV_NAME1 "LAG Studio"
// Options
#define FS_OFF .5
#define FS_ON 1
#define FRAME_RATE 24
float WINDOW_RATIO = FS_OFF;
// FPS DEBUG
int nFrame = 0;
int oldClock = 0;
int fps = 0;

// PROTOTYPES
void FPS_Info();

#endif // INFO_H_INCLUDED
