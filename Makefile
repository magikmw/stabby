TARGET			:=	stabby
RELEASENAME 	:=	Stabby\ Alpha

CFLAGS			:=	-Wall -std=c99

LD_FLAGS		:=	-Wl,-rpath,. -O3
LD_FLAGS_DEBUG	:=	-Wl,-rpath,. -O0 -ggdb

DEFINES			:= 	-DNAME_VERSION=\"$(RELEASENAME)\"
DEFINES_DEBUG	:=	-DNAME_VERSION=\"$(RELEASENAME)\ DEBUG\" -DDEBUG

INCLUDES		:=	-Isrc -Iinc

LINKS			:= 	-Lbin/libs
LIBRARIES 		:=	-lcsfml-graphics -lcsfml-system -lcsfml-window -lm -lds

SRC_FILES		:= 	StabbyMain.c \
			 		Globals.c \
			 		Architect.c \
			 		UI.c \
			 		Keyboard.c \
			 		Interaction.c \
			 		Graphics.c \
			 		SpiralShadowcasting.c \
			 		Random.c \
			 		Dijkstra.c \
			 		dse.c

OBJ_DIR			:= 	obj/
SRC_DIR			:= 	src/
BIN_DIR			:=	bin/

OBJ_FILES		:=	$(addsuffix .o, $(basename $(SRC_FILES)))
OBJ_FILES		:=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(BIN_DIR)$(TARGET)

debug: LD_FLAGS	:= $(LD_FLAGS_DEBUG)
debug: DEFINES 	:= $(DEFINES_DEBUG)
debug: $(BIN_DIR)$(TARGET)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc $(CFLAGS) $(INCLUDES) $(DEFINES) -g -o $@ -c $< 

$(BIN_DIR)$(TARGET): _makedirs $(OBJ_FILES)
	gcc -o $(BIN_DIR)$(TARGET) $(OBJ_FILES) $(LIBRARIES) $(LINKS) $(LD_FLAGS)

_makedirs:
	mkdir -p $(OBJ_DIR)

clean: 
	rm -fr $(OBJ_DIR) $(BIN_DIR)$(TARGET)

run:
	cd $(BIN_DIR) && ./$(TARGET)

info:
	@echo "TARGET:		$(BIN_DIR)$(TARGET)"
	@echo "SRC_FILES:	$(SRC_FILES)"
	@echo "OBJ_FILES:	$(OBJ_FILES)"
	@echo "LINKS:		$(LINKS)"
	@echo "LIBRARIES:	$(LIBRARIES)"