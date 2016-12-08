#ifndef _H_NDS_
#define _H_NDS_
#include <ds2io.h>
#include <ds2_cpu.h>
#include <ds2_malloc.h>
#define memalign(n, size) malloc(size)

#define SCREEN_WIDTH	256
#define SCREEN_HEIGHT	192

#define FONT_WIDTH	12
#define FONT_HEIGHT 12

/* main.cpp */
extern int nGameStage;
extern int bGameRunning;
extern char szAppCachePath[];
extern unsigned int debugValue[2];
void resetGame();

/* ui.cpp */
#define UI_COLOR	R8G8B8_to_B5G6R5(0xffffff)
#define UI_BGCOLOR	R8G8B8_to_B5G6R5(0x102030)

extern char ui_current_path[];
extern void setGameStage(int stage);
int do_ui_key(unsigned int key);

void draw_ui_main();
void draw_ui_browse(bool rebuiltlist);

void ui_update_progress(float size, char * txt);
void ui_update_progress2(float size, const char * txt);
extern short gameSpeedCtrl;
extern unsigned int hotButtons;

/* roms.cpp */
#ifdef __cplusplus
extern "C" int findRomsInDir(int force);
#endif
char * getRomsFileName(int idx);
int getRomsFileStat(int idx);

/* gui.cpp */
void init_gui();
void exit_gui();
void update_gui();
void configureVertices();
void drawPreview();
/* bzip */
extern char szAppRomPath[];

/* drv */
extern int drvWidth;
extern int drvHeight;
extern int iAdd;
extern int iModulo;
extern int xOff;
extern int yOff;
#ifdef __cplusplus
extern "C" int DrvInit(int nDrvNum, bool bRestore);
#endif
int DrvExit();

/* input */
int InpInit();
int InpExit();
void InpDIP();
int InpMake(unsigned int);
void loadDefaultInput();

/* snd.cpp */
#define SND_RATE		22050
#define SND_FRAME_SIZE	((SND_RATE * 100 + 5999) / 6000)

extern int mixbufidDiff;
extern unsigned char monoSound;
int sound_start();
int sound_stop();
void sound_next();
void sound_pause();
void sound_continue();

#endif	// _H_NDS_
