/*
    Architect.c is a part of Stabby
    Copyright (C) 2013 Michał Walczak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include "Stabby.h"
#include "IncludeGlobals.h"

Edge* alloc_edge(void);
void clearMap(void);
void fillMap(void);

Edge* makeWall(int direction);
void makeBorders(int x, int y, int w, int h, char* mod);
Room* makeRoom(Rect* rect);
void delRoom(Room* room);
Rect* makeRect(int x, int y, int w, int h);
void delRect(Rect* rect);
void lightRooms(int lightness);

boolean checkIntersection(Rect* this, Room* other);

void makeCorridorH(int x1, int x2, int y);
void makeCorridorV(int y1, int y2, int x);

void createMap(void){
    #ifdef DEBUG
    sfClock* timer = sfClock_create();
    static int tries = 0;
    #endif

    clearMap();

    rooms_number = 0;
    Rect* temp_rect;
    while(true){
        makeBorders(0, 0, MAP_X, MAP_Y, "in"); // make map edge walls
        rooms_number = 0;

        for(int i = 0; i < MAX_ROOMS; i++){

            int w = randInt(ROOM_MIN_SIZE, ROOM_MAX_SIZE);
            int h = randInt(ROOM_MIN_SIZE, ROOM_MAX_SIZE);
            int x = randInt(0, MAP_X - w - 1);
            int y = randInt(0, MAP_Y - h - 1);

            temp_rect = makeRect(x,y,w,h);

            if(i == 0){
                rooms[rooms_number++] = makeRoom(temp_rect);
            }
            else{
                boolean intersects = false;
                for(int j = 0; j < rooms_number; j++){
                    intersects = checkIntersection(temp_rect, rooms[j]);
                    // printf("intersects: %i\n", intersects);
                    if(intersects == true) break;
                }
                if(intersects == false)
                    rooms[rooms_number++] = makeRoom(temp_rect);
            }

            delRect(temp_rect);
        }
        if(rooms_number >= MIN_ROOMS) break;
        else{
            for(int i = 0; i < rooms_number; i++){
                delRoom(rooms[i]);
            }
            // printf("Clearing the map\n");
            clearMap();
            #ifdef DEBUG
            tries++;
            #endif
            // printf("Not enough rooms\n");
        }
    }

    fillMap(); // fill the map with walls before carving out corridors

    // connect the rooms with corridors
    for(int i=0; i < rooms_number-1; i++){
        sfVector2i one = roomCenter(rooms[i]);
        sfVector2i two = roomCenter(rooms[i+1]);
        // printf("one: x:%.0f, y:%.0f\n",one.x,one.y);
        // printf("two: x:%.0f, y:%.0f\n",two.x,two.y);
        if(randInt(0, 1) == 1){ // go horizontal, then vertical
            makeCorridorH(one.x, two.x, one.y);
            makeCorridorV(one.y, two.y, two.x);
        }
        else{
            makeCorridorV(one.y, two.y, one.x);
            makeCorridorH(one.x, two.x, two.y);
        }
    }

    // Light rooms up
    lightRooms(50);

    #ifdef DEBUG
        printf("[INFO] Mapgen tries: %i, time: %llims, rooms created: %i\n", tries, sfClock_getElapsedTime(timer).microseconds/1000, rooms_number);
        sfClock_destroy(timer);
    #endif

    // when finished, render it all
    makeMapSprites();
}

Edge* alloc_edge(void)
{
    return (Edge*) calloc(1, sizeof(Edge) +1);
}

void delEdge(Edge* edge){
    if(edge != NULL)
        free(edge);
}

Edge* makeWall(int direction)
{
    Edge* temp_ptr = alloc_edge();
    switch(direction)
    {
        case N:
        {
            temp_ptr -> N = true;
            break;
        }
        case S:
        {
            temp_ptr -> S = true;
            break;
        }
        case W:
        {
            temp_ptr -> W = true;
            break;
        }
        case E:
        {
            temp_ptr -> E = true;
            break;
        }
    }

    return temp_ptr;
}

void makeBorders(int point_x, int point_y, int w, int h, char* mod)
{
    // printf("makeBorders() call strcmp(mod, in): %i\n", strcmp(mod, "in"));

    // printf("makeBorders() call, x:%i, y:%i, w:%i, h:%i \n", point_x, point_y, w, h);

    int mode = 3; // mode flag - 0 for in, 1 of out, 2 for both

    if(strcmp(mod, "in") == 0)
        mode = 0;
    else if(strcmp(mod, "out") == 0)
        mode = 1;
    else if(strcmp(mod, "both") == 0)
        mode = 2;
    else
        printf("makeBorders(): ERROR, WRONG MODE PROVIDED: %s\n", mod);

    // printf("makeBorders(): %i\n", mode);

    if(mode == 0 || mode == 2)
    {
        // printf("in executed\n");
        for(int x=point_x; x < point_x+w; x++)
            for(int y=point_y; y < point_y+h; y++) {
                if(x == point_x)
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeWall(W);
                    else
                        map[MAP_X * y + x].edge -> W = true;
                }
                if(x == point_x + w-1)
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeWall(E);
                    else
                        map[MAP_X * y + x].edge -> E = true;
                }
                if(y == point_y)
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeWall(N);
                    else
                        map[MAP_X * y + x].edge -> N = true;
                }
                if(y == point_y + h - 1)
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeWall(S);
                    else
                        map[MAP_X * y + x].edge -> S = true;
                }
            }
    }

    if(mode == 1 || mode == 2)
    {
       for(int x=point_x; x < point_x+w; x++)
            for(int y=point_y; y < point_y+h; y++) {
                if(x == point_x && point_x-1 >= 0)
                {
                    if(map[MAP_X * y + (x-1)].edge == NULL)
                        map[MAP_X * y + (x-1)].edge = makeWall(E);
                    else
                        map[MAP_X * y + (x-1)].edge -> E = true;
                }
                if(x == point_x + w-1 && point_x+w < MAP_X)
                {
                    if(map[MAP_X * y + (x+1)].edge == NULL)
                        map[MAP_X * y + (x+1)].edge = makeWall(W);
                    else
                        map[MAP_X * y + (x+1)].edge -> W = true;
                }
                if(y == point_y && point_y -1 >= 0)
                {
                    if(map[MAP_X * (y-1) + x].edge == NULL)
                        map[MAP_X * (y-1) + x].edge = makeWall(S);
                    else
                        map[MAP_X * (y-1) + x].edge -> S = true;
                }
                if(y == point_y + h - 1 && point_y+h < MAP_Y)
                {
                    if(map[MAP_X * (y+1) + x].edge == NULL)
                        map[MAP_X * (y+1) + x].edge = makeWall(N);
                    else
                        map[MAP_X * (y+1) + x].edge -> N = true;
                }
            }
    }
}

boolean hasEdges(int x, int y){
    if(isMap(x, y) == false || map[MAP_COORD(x,y)].edge == NULL)
        return false;
    else
        return true;
}

boolean hasAllEdges(int x, int y){

    if(hasEdges(x,y)
            && map[MAP_COORD(x,y)].edge -> N
                && map[MAP_COORD(x,y)].edge -> S
                    && map[MAP_COORD(x,y)].edge -> E
                        && map[MAP_COORD(x,y)].edge -> W)
        return true;
    else
        return false;
}

boolean isMap(int x, int y){
    if(x < 0 || x >= MAP_X || y < 0 || y >= MAP_Y)
        return false;
    else
        return true;
}

// mapgen
Rect* allocRect(void)
{
    return (Rect*) calloc(1, sizeof(Rect) +1);
}

void delRect(Rect* rect){
    if(rect != NULL)
        free(rect);
}

void lightRooms(int lightness){
    // iterates through all the rooms and sets lightness% of them to lit
    for(int i=0; i < rooms_number; i++){
        if(randInt(0,100) < lightness){
            // printf("Lit room\n");
            for(int x = rooms[i] -> x1; x < rooms[i] -> x2; x++)
                for(int y = rooms[i] -> y1; y < rooms[i] -> y2; y++)
                    map[MAP_COORD(x,y)].light = true;
        }
    }
}

Rect* makeRect(int x, int y, int w, int h){
    Rect * temp;

    temp = allocRect();

    temp -> x1 = x;
    temp -> y1 = y;
    temp -> x2 = x + w;
    temp -> y2 = y + h;

    return temp;
}

boolean checkIntersection(Rect* this, Room* other){
    return (this -> x1 <= other -> x2 && this -> x2 >= other -> x1 && this -> y1 <= other -> y2 && this -> y2 >= other -> y1);
}

Room* allocRoom(void){
    return (Room*) calloc(1, sizeof(Room) +1);
}

void delRoom(Room* room){
    if (room != NULL)
        free(room);
}

Room* makeRoom(Rect* rect){
    Room* temp = allocRoom();

    temp -> x1 = rect -> x1;
    temp -> y1 = rect -> y1;
    temp -> x2 = rect -> x2;
    temp -> y2 = rect -> y2;

    makeBorders(temp -> x1, temp -> y1, temp -> x2 - temp -> x1, temp -> y2 - temp -> y1, "both");

    return temp;
}

sfVector2i roomCenter(Room* room){
    int x = (room -> x1 + room -> x2) / 2;
    int y = (room -> y1 + room -> y2) / 2;
    return  (sfVector2i){x,y};
}

void clearMap(void){
    // printf("Clear map\n--\n");
    for(int x=0; x < MAP_X; x++)
        for(int y=0; y < MAP_Y; y++) {
            if(hasEdges(x,y)){
                map[MAP_COORD(x,y)].edge -> N = false;
                map[MAP_COORD(x,y)].edge -> E = false;
                map[MAP_COORD(x,y)].edge -> S = false;
                map[MAP_COORD(x,y)].edge -> W = false;
            }
            map[MAP_COORD(x,y)].corridor = false;
            map[MAP_COORD(x,y)].corridor_end = false;
            map[MAP_COORD(x,y)].light = false;
        }
}

Room* isInRoom(int x, int y){   // return a pointer to a room if the point is in it, otherwise NULL
    int i;
    Room* temp = NULL;
    for(i=0; i < rooms_number; i++){
        temp = rooms[i];
        if(temp -> x1 <= x && x < temp -> x2 && temp -> y1 <= y && y < temp -> y2) break;
    }
    if(i < rooms_number)
        return temp;
    else
        return NULL;
}

void fillMap(void){
    for(int x=0; x < MAP_X; x++)
        for(int y=0; y < MAP_Y; y++) {
            if(isInRoom(x,y) == NULL){
                if(hasEdges(x,y)){
                    map[MAP_COORD(x,y)].edge -> N = true;
                    map[MAP_COORD(x,y)].edge -> E = true;
                    map[MAP_COORD(x,y)].edge -> S = true;
                    map[MAP_COORD(x,y)].edge -> W = true;
                }
                else{
                    makeBorders(x,y,1,1,"in");
                }
            }
        }
}

void makeCorridorH(int x1, int x2, int y){
    // printf("makeCorridorH() x1:%i, x2:%i, y:%i\n", x1, x2, y);
    Room* temp_room = NULL;
    for(int x=MIN(x1,x2); x <= MAX(x1,x2); x++){
        if((temp_room = isInRoom(x,y)) == NULL){
            if(x == MIN(x1,x2)){
                map[MAP_COORD(x,y)].edge -> E = false;
            }
            else if(x == MAX(x1,x2)){
                map[MAP_COORD(x,y)].edge -> W = false;
            }
            else{
                map[MAP_COORD(x,y)].edge -> W = false;
                map[MAP_COORD(x,y)].edge -> E = false;
            }

            map[MAP_COORD(x,y)].corridor = true;
            map[MAP_COORD(x,y)].light = false;
        }
        else{
            if(x == temp_room -> x1 && x != MIN(x1,x2)){
                map[MAP_COORD(x,y)].edge -> W = false;
            }
            else if(x == temp_room -> x2-1 && x != MAX(x1,x2)){
                map[MAP_COORD(x,y)].edge -> E = false;
            }
        }
        // if(x == MIN(x1,x2) || x == MAX(x1,x2)){
        //     map[MAP_COORD(x,y)].corridor_end = true;
        // }
    }
}

void makeCorridorV(int y1, int y2, int x){
    // printf("makeCorridorV() y1:%i, y2:%i, x:%i\n", y1, y2, x);
    Room* temp_room = NULL;
    for(int y=MIN(y1,y2); y <= MAX(y1,y2); y++){
        temp_room = isInRoom(x,y);
        if(temp_room == NULL){
            if(y == MIN(y1,y2)){
                map[MAP_COORD(x,y)].edge -> S = false;
            }
            else if(y == MAX(y1,y2)){
                map[MAP_COORD(x,y)].edge -> N = false;
            }
            else{
                map[MAP_COORD(x,y)].edge -> N = false;
                map[MAP_COORD(x,y)].edge -> S = false;
            }
            map[MAP_COORD(x,y)].corridor = true;
            map[MAP_COORD(x,y)].light = false;
        }
        else{
            if(y == temp_room -> y1 && y != MIN(y1,y2)){
                map[MAP_COORD(x,y)].edge -> N = false;
            }
            else if(y == temp_room -> y2-1 && y != MAX(y1,y2)){
                map[MAP_COORD(x,y)].edge -> S = false;
            }
        }
    //     if(y == MIN(y1,y2) || y == MAX(y1,y2)){
    //         map[MAP_COORD(x,y)].corridor_end = true;
    //     }
    }
}
