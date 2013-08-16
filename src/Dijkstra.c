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

void DMapCreate(DMap* dmap){
    // Create an empty DMap with just data structures ready
    dmap->poi_list = create_list();
    dmap->poi_list_flag = false;
    dmap->frontier = create_list();
}

void DMapAddPOI(DMap* dmap, int position){
    // Add given position to the value list if it's not already in
    list_iter_p iterator = list_iterator(dmap->poi_list, FRONT);

    int* temp_position = NULL;
    if(dmap->poi_list->first != NULL){
        temp_position = (int*)dmap->poi_list->first->data;
    }
    
    if(temp_position == NULL){ // list empty, add position
        list_add(dmap->poi_list, &position, sizeof(int));
        dmap->poi_list_flag = true;
    }
    else{ // list not empty
        boolean found = false;
        while(temp_position != NULL && found == false){ // search for the position
            temp_position = (int*)list_next(iterator);
            if(temp_position != NULL){
                printf("Iter: %i\n", *temp_position);
                if(*temp_position == position){
                    found = true;
                }
            }
        }
        if(!found){ // not found in the list, add the position
            list_add(dmap->poi_list, &position, sizeof(int));
            dmap->poi_list_flag = true;
        }
        #ifdef DEBUG
        else{
            printf("[WARNING] Trying to add a POI to the DMap twice!\n");
        }
        #endif
    }

}

void DMapRemPOI(DMap* dmap, int position){
    // Search the value list and remove the position given
    list_iter_p iterator = list_iterator(dmap->poi_list, FRONT);

    int* temp_position = NULL;
    if(dmap->poi_list->first != NULL){
        temp_position = (int*)dmap->poi_list->first->data;
    }

    if(temp_position == NULL){ // list empty, nothing to remove!
        #ifdef DEBUG
            printf("[WARNING] Trying to remove POI from an empty DMap list!\n");
        #endif
        printf("%p\n", dmap->poi_list->first);
        return;
    }
    else{
        boolean found = false;
        while(temp_position != NULL && found == false){ // search for the position
            temp_position = (int*)list_next(iterator);
            if(temp_position != NULL){
                if(*temp_position == position){
                    found = true;
                }
            }
        }
        if(found){ // item found, removing
            list_pluck(dmap->poi_list, iterator->current);
            dmap->poi_list_flag = true;
        }
        #ifdef DEBUG
        else{
            printf("[WARNING] Trying remove a POI that's not on the list!\n");
        }
        #endif
    }
}

void DMapUpdate(DMap* dmap){
    // Function updates given DMap according to it's own POI list and the wall map
    if(dmap->poi_list_flag){
        dmap->poi_list_flag = false;
        for(int x = 0; x < MAP_X; x++){
            for(int y = 0; y < MAP_Y; y++){
                if(hasAllEdges(x,y)){ // fully walled off
                    dmap->value_map[MAP_COORD(x,y)] = -(INFINITE_DISTANCE);
                }
                else{ // free floor tiles
                    dmap->value_map[MAP_COORD(x,y)] = INFINITE_DISTANCE;
                }
            }
        }
        list_iter_p iterator = list_iterator(dmap->poi_list, FRONT);
    
        int* temp_position = NULL;
        if(dmap->poi_list->first != NULL){
            temp_position = (int*)dmap->poi_list->first->data;
        }

        while(temp_position != NULL){
            dmap->value_map[*temp_position] = 0;
            addToFrontier(dmap->frontier, dmap->value_map, *temp_position);
            temp_position = (int*)list_next(iterator);
        }

        temp_position = (int*)list_poll(dmap->frontier);
        while(temp_position != NULL){
            for(int n = N; n <= SW; n++){
                if(checkCollision((sfVector2f){map[*temp_position].x, map[*temp_position].y}, n) // n points to directions enum
                    && dmap->value_map[(*temp_position)+neighbours[n]] > dmap->value_map[*temp_position]){
                        dmap->value_map[(*temp_position)+neighbours[n]] = dmap->value_map[*temp_position] + 1;
                        addToFrontier(dmap->frontier, dmap->value_map, (*temp_position)+neighbours[n]);
                }
            }            
            temp_position = (int*)list_poll(dmap->frontier);
        }
        free(iterator);
        free(temp_position);
    }
    // #ifdef DEBUG
    // else{
    //     printf("[INFO] DMap flag not set, not updating.\n");
    // }
    // #endif
}

void DMapDestroy(DMap* dmap){
    // Free all lists up.
    destroy_list(dmap->poi_list);
    destroy_list(dmap->frontier);
}

int DMapFollow(DMap* dmap, int current){
    // Return the next direction to move 'downhill' to from current - random if there is a choice
    int next = -1;

    int neighbour_values[8] = { [N...SW] = INFINITE_DISTANCE };
    int lowest = INFINITE_DISTANCE;

    for(int n = N; n <= SW; n++){
        if(checkCollision((sfVector2f){map[current].x, map[current].y}, n)){
            neighbour_values[n] = dmap->value_map[current+neighbours[n]];
        }
        if(neighbour_values[n] != -(INFINITE_DISTANCE) && neighbour_values[n] < lowest){
            lowest = neighbour_values[n];
        }
    }

    int n_lowest = 0;

    for(int n = N; n <= SW; n++){
        if(neighbour_values[n] == lowest){
            n_lowest++;
        }
    }

    if(n_lowest > 1){ // more than one lowest value tile
        int random = randInt(1,n_lowest);
        for(int n = N; n <= SW; n++){
            if(neighbour_values[n] == lowest && --random == 0){
                next = n;
                break;
            }
        }
    }
    else{
        for(int n = N; n <= SW; n++){
            if(neighbour_values[n] == lowest){
                next = n;
                break;
            }
        }   
    }

    return next;
}

void addToFrontier(list_p frontier, int* value_map, int position){
    // Function adds a tile position to the frontier, sorting it by value from lowest
    list_iter_p iterator = list_iterator(frontier, FRONT);

    int* temp_position = NULL;
    if(frontier->first != NULL){
        temp_position = (int*)frontier->first->data;
    }

    if(temp_position == NULL){
    // frontier is empty - add to the end
        list_add(frontier, &position, sizeof(int));
    }
    else if(*temp_position == position){
        return;
    }
    else{
    // otherwise place it before any higher valued position already in
        while(temp_position != NULL && value_map[*temp_position] <= value_map[position]){
            temp_position = (int*)list_next(iterator);
            if(temp_position != NULL && *temp_position == position){
                return;
            }
        }
        if(temp_position == NULL){ // reached the end of the frontier
            list_add(frontier, &position, sizeof(int));
        }
        else{ // found a higher value, placing the item after it's previous one (syntax...)
            list_insert(frontier, iterator->current->prev, &position, sizeof(int));
        }
    }
}
