#include "../include/aim.h"

unsigned int RandomSeed(int size) {

    // Generate random int from "/dev/urandom" used as the seed
    FILE *f;
    unsigned int buff[size];
    unsigned int seed = 0;

    f = fopen("/dev/urandom","r");
    fread(buff,size,1,f);

    // Sum of the entire array (buff)
    for(int i = 0;i<size;i++,seed+=buff[i]);

    fclose(f);
    return seed;
}

void Centering(int w, int * xpos, int * ypos) {

    // Store row and col on the screen
    int     row,col;
    getmaxyx(stdscr,row,col);
    * xpos = (col-w)/2; * ypos = 2;
}

int DrawASCIIFigure(char ** figure, int x, int y, const int n) {

    int     tmp = y;

    if(n<1) return 0;

    for(int i = 0;i<n;i++){
        for(int ii = 0,y;figure[ii];ii++,tmp++)
            mvprintw(tmp,x,figure[ii]);
        tmp++;
    }
    return tmp;
}

int CheckTerminalSize(void){

    getmaxyx(stdscr,TERMINAL_SIZE[0],TERMINAL_SIZE[1]);
    return ((TERMINAL_SIZE[0] >= 29) && (TERMINAL_SIZE[1] >= 100));
}