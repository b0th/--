#include "../include/aim.h"

    int THREAD_END     = 0;
    int TARGET_COUNT   = 0;
    int TARGET_REACHED = 0;
    target * CURRENT_TARGET;

int aim_trainer(void) {

    // Mouse event (event type: struct)
    MEVENT event;

    target * head = NULL;
    int     x,y,height,width,key;
    pthread_t thread;

    // Clear stdscr
    clear();

    // Linked list initialization with a first target
    head = (target * )malloc(sizeof(target));
    if (head == NULL) exit(0);
    head = target_create(0,0,0,0,NULL);

    // Fill the list
    for(int i = 0;i<MAX_TARGETS+2;i++) {
        height      = (rand()%(5-1))+2;  
        width       = height*2;
        x           = (rand()%(TERMINAL_SIZE[1]-width-1)+2);
        y           = (rand()%(TERMINAL_SIZE[0]-height-1)+2);
        target_append(head, x, y, height, width);
    }

    head = head->next;
    CURRENT_TARGET = head;

    // Running a new thread that displays square
    pthread_create(&thread, NULL, target_display_all, NULL);

    while(!THREAD_END)
    {   
        key = wgetch(stdscr);
		switch(key)
        { case KEY_MOUSE:
			if(getmouse(&event) == OK) {	
                if(event.bstate & BUTTON1_PRESSED) {
                    if (target_check(event, CURRENT_TARGET)){
                        TARGET_REACHED++;
                }
            }     
        }
        break;
        case 'q': endwin(); exit(0);
    }

}
    sleep(1);
    return 1;
}