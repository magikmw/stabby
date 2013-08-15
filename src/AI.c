/*
    AI.c is a part of Stabby
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

/* Comment legend:
    ->  Non-critical feature, to be iterated towards
*/

// Different FOV range in different states? [adjust via function arguments]

void Plain_Standby(Entity* mob)
{
    // Check previously calculated FOV if present [position list]
        // Act on things found in FOV
            // if something strange happens? - change to alerted, set counter, run alerted, return;
            // if the player is detected - change to pursue, set counter, run pursue, return;

    // Wander about
        // Get back to light if in darkness
        // Move about randomly -> patrol

    // Run FOV, add positions to a position list
}

void Plain_Alerted(Entity* mob)
{
    // Check previously calculated FOV if present [position list]
        // Act on things found in FOV
            // no player? -- the counter, if it's 0, change to standby, run standby, return;
            // if something strange happens? - reset the counter
            // if the player is detected - change to pursue, set counter, run pursue, return;

    // Move using DMap_PlayerLastSeen -> if in tunnel, continue until you exit
        // -> perhaps allow moving without turning for <= 45 turns [searching, right]?

    // Run FOV, add positions to a position list
}

void Plain_Pursue(Entity* mob)
{
    // Check previously calculated FOV if present [position list]
        // Act on things found in FOV
            // if the player is detected - reset counter
            // no player? -- the counter, if it's 0, change to alerted, set counter, run alerted, return;

    // Move using DMap_PlayerChase -> if in tunnel, continue until you exit
        // -> perhaps allow moving without turning for <= 90 turns [running, right]?

    // Run FOV, add positions to a position list
}
