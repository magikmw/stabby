/*
    UI.c is a part of Stabby
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

void createStaticUI(void)
{
    staticUI[0] = sfSprite_create();
    sfSprite_setTexture(staticUI[0], textureArray[1], sfTrue);
    sfSprite_setTextureRect(staticUI[0], (sfIntRect){0,0, 960, 14});

    staticUI[1] = sfSprite_create();
    sfSprite_setTexture(staticUI[1], textureArray[1], sfTrue);
    sfSprite_setTextureRect(staticUI[1], (sfIntRect){0,14, 960, 14});
    sfSprite_setPosition(staticUI[1], (sfVector2f){0, WINDOW_Y-BORDER_OFFSET});

    staticUI[2] = sfSprite_create();
    sfSprite_setTexture(staticUI[2], textureArray[1], sfTrue);
    sfSprite_setTextureRect(staticUI[2], (sfIntRect){0,28, 540, 14});
    sfSprite_setPosition(staticUI[2], (sfVector2f){BORDER_OFFSET, 0});
    sfSprite_setRotation(staticUI[2], 90);

    staticUI[3] = sfSprite_create();
    sfSprite_setTexture(staticUI[3], textureArray[1], sfTrue);
    sfSprite_setTextureRect(staticUI[3], (sfIntRect){0,42, 540, 14});
    sfSprite_setPosition(staticUI[3], (sfVector2f){WINDOW_X, 0});
    sfSprite_setRotation(staticUI[3], 90);

    staticUI[4] = sfSprite_create();
    sfSprite_setTexture(staticUI[4], textureArray[1], sfTrue);
    sfSprite_setTextureRect(staticUI[4], (sfIntRect){0,56, 540, 14});
    sfSprite_setPosition(staticUI[4], (sfVector2f){PANEL_ZERO_X+BORDER_OFFSET, 0});
    sfSprite_setRotation(staticUI[4], 90);
}
