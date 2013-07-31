/*
    Dijkstra.c is a part of Stabby
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

void DMapCreate(DMap dmap){
    // Create an empty DMap with just data structures ready
    dmap.poi_list = create_list();
    dmap.poi_list_flag = false;
    dmap.frontier = create_list();
}

void DMapAddPOI(DMap dmap, int position){
    // Add given position to the value list if it's not already in
    list_iter_p iterator = list_iterator(dmap.poi_list, FRONT);
    int* temp_position = (int*)list_current(iterator);
    if(temp_position == NULL){ // list empty, add position
        list_add(dmap.poi_list, &position, sizeof(int));
    }
    else{ // list not empty
        boolean found = false;
        while(temp_position != NULL && found == false){ // search for the position
            temp_position = (int*)list_next(iterator);
            if(temp_position != NULL){
                if(*temp_position == position){
                    found = true;
                }
            }
        }
        if(!found){ // not found in the list, add the position
            list_add(dmap.poi_list, &position, sizeof(int));
        }
        #ifdef DEBUG
        else{
            printf("[WARNING] Trying to add a position to the DMap twice!\n");
        }
        #endif
    }

}

void DMapRemPOI(DMap dmap, int position){
    // [TODO] Search the value vector and remove the position given
}

void DMapUpdate(DMap dmap){
    // [TODO] Function updates given DMap according to it's own POI vector and the wall map
}

void DMapDestroy(DMap dmap){
    // Free all lists up.
    destroy_list(dmap.poi_list);
    destroy_list(dmap.frontier);
}

void addToFrontier(vector_p frontier, int* value_map, int position){
    // [TODO] Function adds a tile position to the frontier, sorting it by value from lowest
}