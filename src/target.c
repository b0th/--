#include "../include/aim.h"

target * target_create(int x, int y, int height, int width, target * next) {

    target * new_target = (target *)malloc(sizeof(target));

    if (new_target == NULL) {
        printf("Error creating a new target\n");
        exit(0);
    }

    // Assignment of attrs
    new_target->x      = x;         new_target->y     = y;
    new_target->height = height;    new_target->width = width;
    new_target->next   = next;

    return new_target;
}

void target_append(target * head, int x, int y, int height, int width) {

    if(head == NULL) {
        head = target_create(x,y,height,width,NULL);
        return;
    }

    // Go throught until the end
    target * cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    // Create a new target
    target * new_target = target_create(x,y,height,width,NULL);
    cursor->next = new_target;
}

void target_display(int x, int y, int height, int width, char c) {

    int end_y = y + height;
    int end_x = x + width;
    int tmp_x;

    for(y;y<end_y;y++) {
        for(tmp_x = x;tmp_x<end_x;tmp_x++) {
            mvaddch(y,tmp_x,c);
        }
    }
    refresh();
}

void * target_display_all(void *vargp) {

    target * cursor = CURRENT_TARGET;
    int random_color;

    while(cursor->next != NULL){
        CURRENT_TARGET = cursor;
        random_color = (rand()%(7-1))+1;
        mvprintw(1,1,"[%d/%d]",TARGET_COUNT,MAX_TARGETS);

        if(TARGET_COUNT > 0)
            mvprintw(1,10,"accuracy %.2f%%",(float)TARGET_REACHED / TARGET_COUNT *100.0);

        attron(COLOR_PAIR(random_color));
        target_display(cursor->x,cursor->y,cursor->height,cursor->width,'X');
        attroff(COLOR_PAIR(random_color));
        
        napms(MILLISECONDS);
        refresh();
        target_display(cursor->x,cursor->y,cursor->height,cursor->width,' ');

        TARGET_COUNT++;
        cursor = cursor->next;
    }

    THREAD_END = 1;
}

int target_check(MEVENT e, target * t) {
    
    int x     = t->x;         int y      = t->y;
    int width = t->width;     int height = t->height;
    // Check if cursor is on a target
    return ((x <= e.x) && (e.x <= x+width) && (y <= e.y) && (e.y<= y+height));
}