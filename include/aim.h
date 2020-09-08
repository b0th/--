#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define ARRAY_SIZE 50
#define MAX_TARGETS 60
#define MILLISECONDS 600

int TERMINAL_SIZE[2];

extern int THREAD_END;
extern int TARGET_COUNT;
extern int TARGET_REACHED;

typedef struct target{

    int x;
    int y;
    int height;
    int width;
    struct target * next;

} target;

extern target * CURRENT_TARGET;

// set_colors.c
void init_color_set(void);

// utilities.c
unsigned int RandomSeed(int size);
void Centering(int w, int * xpos, int * ypos);
int DrawASCIIFigure(char ** figure, int x, int y, const int n);
int CheckTerminalSize(void);

// target.c
target * target_create(int x, int y, int height, int width, target * next);
void target_append(target * head, int x, int y, int height, int width);
void target_display(int x, int y, int height, int width, char c);
void * target_display_all(void *vargp);
int target_check(MEVENT e, target * t);

// aim-trainer.c
int aim_trainer(void);