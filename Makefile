    # Makefile is a part of Stabby
    # Copyright (C) 2013 Michał Walczak

    # This program is free software: you can redistribute it and/or modify
    # it under the terms of the GNU General Public License as published by
    # the Free Software Foundation, either version 3 of the License, or
    # (at your option) any later version.

    # This program is distributed in the hope that it will be useful,
    # but WITHOUT ANY WARRANTY; without even the implied warranty of
    # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    # GNU General Public License for more details.

    # You should have received a copy of the GNU General Public License
    # along with this program.  If not, see http://www.gnu.org/licenses/.

# Executable name
TARGET			:=	stabby
# Window title - remember to escape special characters (inc. spaces)
RELEASENAME 	:=	Stabby\ Alpha

# Compiler flags
CFLAGS			:=	-Wall -std=c99

# Linker flags for both release and debug builds
LD_FLAGS		:=	-Wl,-rpath,. -O3
LD_FLAGS_DEBUG	:=	-Wl,-rpath,. -O0 -ggdb

# Defines for both release and debug builds - remember to escape characters
DEFINES			:= 	-DNAME_VERSION=\"$(RELEASENAME)\"
DEFINES_DEBUG	:=	-DNAME_VERSION=\"$(RELEASENAME)\ DEBUG\" -DDEBUG

# Include directories
INCLUDES		:=	-Isrc -Iinc

# Linking directories
LINKS			:= 	-Lbin/libs
# Linked libraries
LIBRARIES 		:=	-lcsfml-graphics -lcsfml-system -lcsfml-window -lm -lds

# Source files, without the path (assumed only one source dir exists)
SRC_FILES		:= 	StabbyMain.c \
			 		Globals.c \
			 		Architect.c \
			 		UI.c \
			 		Keyboard.c \
			 		Interaction.c \
			 		Graphics.c \
			 		SpiralShadowcasting.c \
			 		Random.c \
			 		Dijkstra.c

# Directory pathnames
OBJ_DIR			:= 	obj/
SRC_DIR			:= 	src/
BIN_DIR			:=	bin/

# Figuring out the names for .o files
OBJ_FILES		:=	$(addsuffix .o, $(basename $(SRC_FILES)))
OBJ_FILES		:=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(BIN_DIR)$(TARGET)

# Assign the proper flags and defines for the debug build
debug: LD_FLAGS	:= $(LD_FLAGS_DEBUG)
debug: DEFINES 	:= $(DEFINES_DEBUG)
debug: $(BIN_DIR)$(TARGET)

# Linking target
$(BIN_DIR)$(TARGET): _makedirs $(OBJ_FILES)
	gcc -o $(BIN_DIR)$(TARGET) $(OBJ_FILES) $(LIBRARIES) $(LINKS) $(LD_FLAGS)

# Compile target
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc $(CFLAGS) $(INCLUDES) $(DEFINES) -g -o $@ -c $< 

# Create varios directories as needed
_makedirs:
	mkdir -p $(OBJ_DIR)

clean: 
	rm -fr $(OBJ_DIR) $(BIN_DIR)$(TARGET)

run: all
	cd $(BIN_DIR) && ./$(TARGET)

# Runs the debugger, requires debug build
run_gdb: debug
	cd $(BIN_DIR) && gdb ./$(TARGET)

info:
	@echo "TARGET:		$(BIN_DIR)$(TARGET)"
	@echo "SRC_FILES:	$(SRC_FILES)"
	@echo "OBJ_FILES:	$(OBJ_FILES)"
	@echo "LINKS:		$(LINKS)"
	@echo "LIBRARIES:	$(LIBRARIES)"

libds:
	cd lib/libds && make && make ds.h
	cp lib/libds/libds.a $(BIN_DIR)libs/libds.a
	cp lib/libds/ds.h inc/ds.h