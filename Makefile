CC			= gcc

SRC    		=	src/menu.c \
				src/aim-trainer.c \
				src/set_colors.c \
				src/target.c \
				src/utilities.c \
				
NAME   		=  	aim

CFLAGS		+= 	-lncurses -lmenu -lpthread
CFLAGS		+= 	-I./include

OBJ 		= 	$(SRC:.c=.o)

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clear:
	rm -f src/*.o
	rm -f $(NAME)
