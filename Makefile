CFLAGS=-Isrc -Iinc -Lbin/libs -Wall ${DEFINES} -std=c99
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
		 src/Random.c \
		 src/Dijkstra.c \
		 src/dse.c

LIBRARIES =-lcsfml-graphics -lcsfml-system -lcsfml-window -lm -lds

all : bin/stabby

debug :
	gcc -o bin/stabby ${SRCFILES} ${CFLAGS} ${LIBRARIES} -Wl,-rpath,. -O0 -ggdb

bin/stabby :
	gcc -O3 -o bin/stabby ${SRCFILES} ${CFLAGS} ${LIBRARIES} -Wl,-rpath,.

clean : 
	rm -f src/*.o bin/stabby

# [TODO] Add included library building to the makefile/build script.