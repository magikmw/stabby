/*
    Keyboard.c is a part of Stabby
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

int handleKeys(void)
{
    if(sfKeyboard_isKeyPressed(sfKeyNumpad8)){
        player.move(N);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad2)){
        player.move(S);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad4)){
        player.move(W);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad6)){
        player.move(E);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad7)){
        player.move(NW);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad9)){
        player.move(NE);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad1)){
        player.move(SW);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad3)){
        player.move(SE);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyEscape)){
        return 2;
    }
    else
        return 0;
}