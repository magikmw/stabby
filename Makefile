CFLAGS=  -Wall -std=c99 -Wl,-rpath,.
RELEASENAME=\"Stabby\ Alpha\"

INCLUDES = -Isrc -Iinc
LINKS = -Lbin/libs
DEFINES = -DNAME_VERSION=$(RELEASENAME)

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
	gcc -o bin/stabby ${SRCFILES} ${CFLAGS} ${LIBRARIES} -O0 -ggdb -DDEBUG $(INCLUDES) $(LINKS) $(DEFINES)

bin/stabby :
	gcc -O3 -o bin/stabby ${SRCFILES} ${CFLAGS} ${LIBRARIES} -O3 $(INCLUDES) $(LINKS) $(DEFINES)

clean : 
	rm -f src/*.o bin/stabby

# [TODO] Split .o file building and linking
# [TODO] Add included library building to the makefile/build script.