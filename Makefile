CFLAGS=-Isrc -Wall ${DEFINES} -std=c99
RELEASENAME=stabby-0.2

%.o : %.c
	gcc $(CFLAGS) -g -o $@ -c $< 

SRCFILES=src/StabbyMain.c \
		 src/Globals.c \
		 src/Architect.c \
		 src/UI.c \
		 src/Keyboard.c \
		 src/Interaction.c \
		 src/Graphics.c \
		 src/SpiralShadowcasting.c \
		 src/Random.c

LIBRARIES =-lcsfml-graphics -lcsfml-system -lcsfml-window

all : bin/stabby

bin/stabby :
	gcc -O3 -o bin/stabby ${SRCFILES} ${CFLAGS} ${LIBRARIES} -Wl,-rpath,.

clean : 
	rm -f src/*.o bin/stabby
