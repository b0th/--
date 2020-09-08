#include "../include/aim.h"

char *choices[] = {
                        "Aim",
                        "Exit"
                  };

// Crosshair representation
char * crosshair[] = {
                        "    XXXXXXXX",
                        "  XX        XX",
                        "XX     X      XX",
                        "XX   XXXX     XX",
                        "XX     XXXX   XX",
                        "XX      X     XX",
                        "  XX        XX",
                        "    XXXXXXXX",
                        (char*) NULL
                 };

void main(){

    // Initialization functions
    initscr();              // Initialize the window
    cbreak();               // Disable line buffering
    noecho();               // Don't echo any keypresses
    curs_set(FALSE);        // Don't display cursor
    keypad(stdscr, TRUE);   // It enables the reading of function keys(F1,F2,arrows,...)
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    // Terminal is now reporting mouse movement events
    mouseinterval(0);

    // Check terminal size
    if(!CheckTerminalSize()) {
        endwin();
        printf("error: Minimum terminal size: [100x29]\n");
        printf("Current size: [%dx%d]\n",TERMINAL_SIZE[1],TERMINAL_SIZE[0]);
        return;
    }

    // Seed initialization
    srand(RandomSeed(ARRAY_SIZE));

    // Colors initializaion
    start_color();          // Enable colors
    init_color_set();
    

	MENU    * a_menu;
    WINDOW  * a_menu_win;
    ITEM    ** items;
    ITEM    * cur_item;
    int     choices_size = sizeof(choices) / sizeof(char *);
    int     key;
    int     i;

    // Items initializaion
    // +1 because of the end NULL delimiter
    items = (ITEM **)calloc(choices_size+1,sizeof(ITEM *)); 
    for(i = 0;choices[i];i++) 
                       // Name -v    v- Description
        items[i]=new_item(choices[i],"");
    items[choices_size]=(ITEM *)NULL;

    // Create the menu
    a_menu = new_menu((ITEM **)items);

    // Main window displays title/border
    // Sub window displays the menu selectables items
    const int Window_height =   4;
    const int Window_width  =   18;
    int XPOS                =   0;
    int YPOS                =   0;
 
    // Menu options
    set_menu_mark(a_menu, " x ");
    set_menu_fore(a_menu, COLOR_PAIR(1) | A_REVERSE);
    set_menu_back(a_menu, COLOR_PAIR(1));

    Centering(Window_width, &XPOS, &YPOS);

    // Window associated withe the menu
    a_menu_win = newwin(Window_height,Window_width,YPOS,XPOS);
    keypad(a_menu_win, TRUE);

    // Set windows (main and sub) for the menu
    set_menu_win(a_menu, a_menu_win);
    set_menu_sub(a_menu, derwin(a_menu_win, Window_height-2, Window_width-2, 1, 1));

    // Print windows border
    box(a_menu_win, 0, 0);
    refresh();

    // Post menu
    post_menu(a_menu);
    wrefresh(a_menu_win);

    // Print cirle + text
    int last_y = DrawASCIIFigure(crosshair, XPOS+1, 7, 2);
    mvprintw(last_y,XPOS-1,"Terminal Aim Trainer");

    // Loop menu
    while((key = getch()) != 'q')
    {
        switch(key)
        {
            case KEY_DOWN:
                menu_driver(a_menu,REQ_NEXT_ITEM); break;
            case KEY_UP:
               menu_driver(a_menu,REQ_PREV_ITEM); break;
            case 10: // Enter
            {
                const char * ITEM_NAME  =  item_name(current_item(a_menu)); ;
                if          (ITEM_NAME  == "Exit") {endwin(); return;}
                if          (ITEM_NAME  == "Aim")  {aim_trainer();endwin();exit(0);}
                break;
            }
        }
        wrefresh(a_menu_win);
    }
    endwin(); 
}