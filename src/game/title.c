/*
 * File: title.c
 * Author: dgrubb
 * Date: 30/03/2021
 * Description:
 *      Implements the main introductory effect.
 */

#include <jo/jo.h>
#include "game/title.h"
#include "video/video.h"

const jo_color fire_palette_test[] = {
    0, /* Transparent */
    JO_COLOR_RGB(31, 7, 7), /* 31, 7, 7 */
    JO_COLOR_RGB(47, 15, 7), /* 47, 15, 7 */
    JO_COLOR_RGB(71, 15, 7), /* 71, 15, 7 */
    JO_COLOR_RGB(87, 23, 7), /* 87, 23, 7 */
    JO_COLOR_RGB(103, 31, 7), /* 103, 31, 7 */
    JO_COLOR_RGB(119, 31, 7), /* 119, 31, 7 */
    JO_COLOR_RGB(143, 39, 7), /* 143, 39, 7 */
    JO_COLOR_RGB(159, 47, 7), /* 159, 47, 7 */
    JO_COLOR_RGB(175, 63, 7), /* 175, 63, 7 */
    JO_COLOR_RGB(191, 71, 7), /* 191, 71, 7 */
    JO_COLOR_RGB(199, 71, 7), /* 199, 71, 7 */
    JO_COLOR_RGB(223, 79, 7), /* 223, 79, 7 */
    JO_COLOR_RGB(223, 87, 7), /* 223, 87, 7 */
    JO_COLOR_RGB(223, 87, 7), /* 223, 87, 7 */
    JO_COLOR_RGB(215, 95, 7), /* 215, 95, 7 */
    JO_COLOR_RGB(215, 103, 15), /* 215, 103, 15 */
    JO_COLOR_RGB(207, 111, 15), /* 207, 111, 15 */
    JO_COLOR_RGB(207, 119, 15), /* 207, 119, 15 */
    JO_COLOR_RGB(207, 127, 15), /* 207, 127, 15 */
    JO_COLOR_RGB(207, 135, 23), /* 207, 135, 23 */
    JO_COLOR_RGB(199, 135, 23), /* 199, 135, 23 */
    JO_COLOR_RGB(199, 135, 23), /* 199, 135, 23 */
    JO_COLOR_RGB(199, 135, 23), /* 199, 135, 23 */
    JO_COLOR_RGB(199, 151, 31), /* 199, 151, 31 */
    JO_COLOR_RGB(191, 159, 31), /* 191, 159, 31 */
    JO_COLOR_RGB(191, 159, 31), /* 191, 159, 31 */
    JO_COLOR_RGB(191, 167, 39), /* 191, 167, 39 */
    JO_COLOR_RGB(191, 167, 39), /* 191, 167, 39 */
    JO_COLOR_RGB(191, 175, 47), /* 191, 175, 47 */
    JO_COLOR_RGB(183, 175, 47), /* 183, 175, 47 */
    JO_COLOR_RGB(183, 183, 47), /* 183, 183, 47 */
    JO_COLOR_RGB(183, 183, 55), /* 183, 183, 55 */
    JO_COLOR_RGB(207, 207, 111), /* 207, 207, 111 */
    JO_COLOR_RGB(223, 223, 159), /* 223, 223, 159 */
    JO_COLOR_RGB(239, 239, 199), /* 239, 239, 199 */
    JO_COLOR_White

};

/* Pointer to allocated scratch memory for drawing onto */
jo_software_renderer_gfx* fire;
jo_palette fire_palette;
const int fire_width = VIDEO_WIDTH;
const int fire_height = VIDEO_HEIGHT/2;

/* Grabs the content of the progressing fire image
 * and draws it to the correct layer on frame update.
 */
void
title_draw()
{
    jo_software_renderer_flush(fire);
    jo_sprite_draw3D2(fire->sprite_id, 0, VIDEO_HEIGHT-fire_height, 500);
}

/* Allocate VDP1 memeory to use as a crude framebuffer for
 * drawing intermediary fire effect steps onto.
 */
void
title_start()
{
    jo_create_palette(&fire_palette);
    fire_palette.data[0] = 0; /* Transparent */
    fire_palette.data[1] = JO_COLOR_RGB(31, 7, 7); /* 31, 7, 7 */
    fire_palette.data[2] = JO_COLOR_RGB(47, 15, 7); /* 47, 15, 7 */
    fire_palette.data[3] = JO_COLOR_RGB(71, 15, 7); /* 71, 15, 7 */
    fire_palette.data[4] = JO_COLOR_RGB(87, 23, 7); /* 87, 23, 7 */
    fire_palette.data[5] = JO_COLOR_RGB(103, 31, 7); /* 103, 31, 7 */
    fire_palette.data[6] = JO_COLOR_RGB(119, 31, 7); /* 119, 31, 7 */
    fire_palette.data[7] = JO_COLOR_RGB(143, 39, 7); /* 143, 39, 7 */
    fire_palette.data[8] = JO_COLOR_RGB(159, 47, 7); /* 159, 47, 7 */
    fire_palette.data[9] = JO_COLOR_RGB(175, 63, 7); /* 175, 63, 7 */
    fire_palette.data[10] = JO_COLOR_RGB(191, 71, 7); /* 191, 71, 7 */
    fire_palette.data[11] = JO_COLOR_RGB(199, 71, 7); /* 199, 71, 7 */
    fire_palette.data[12] = JO_COLOR_RGB(223, 79, 7); /* 223, 79, 7 */
    fire_palette.data[13] = JO_COLOR_RGB(223, 87, 7); /* 223, 87, 7 */
    fire_palette.data[14] = JO_COLOR_RGB(223, 87, 7); /* 223, 87, 7 */
    fire_palette.data[15] = JO_COLOR_RGB(215, 95, 7); /* 215, 95, 7 */
    fire_palette.data[16] = JO_COLOR_RGB(215, 103, 15); /* 215, 103, 15 */
    fire_palette.data[17] = JO_COLOR_RGB(207, 111, 15); /* 207, 111, 15 */
    fire_palette.data[18] = JO_COLOR_RGB(207, 119, 15); /* 207, 119, 15 */
    fire_palette.data[19] = JO_COLOR_RGB(207, 127, 15); /* 207, 127, 15 */
    fire_palette.data[20] = JO_COLOR_RGB(207, 135, 23); /* 207, 135, 23 */
    fire_palette.data[21] = JO_COLOR_RGB(199, 135, 23); /* 199, 135, 23 */
    fire_palette.data[22] = JO_COLOR_RGB(199, 135, 23); /* 199, 135, 23 */
    fire_palette.data[23] = JO_COLOR_RGB(199, 135, 23); /* 199, 135, 23 */
    fire_palette.data[24] = JO_COLOR_RGB(199, 151, 31); /* 199, 151, 31 */
    fire_palette.data[25] = JO_COLOR_RGB(191, 159, 31); /* 191, 159, 31 */
    fire_palette.data[26] = JO_COLOR_RGB(191, 159, 31); /* 191, 159, 31 */
    fire_palette.data[27] = JO_COLOR_RGB(191, 167, 39); /* 191, 167, 39 */
    fire_palette.data[28] = JO_COLOR_RGB(191, 167, 39); /* 191, 167, 39 */
    fire_palette.data[29] = JO_COLOR_RGB(191, 175, 47); /* 191, 175, 47 */
    fire_palette.data[30] = JO_COLOR_RGB(183, 175, 47); /* 183, 175, 47 */
    fire_palette.data[31] = JO_COLOR_RGB(183, 183, 47); /* 183, 183, 47 */
    fire_palette.data[32] = JO_COLOR_RGB(183, 183, 55); /* 183, 183, 55 */
    fire_palette.data[33] = JO_COLOR_RGB(207, 207, 111); /* 207, 207, 111 */
    fire_palette.data[34] = JO_COLOR_RGB(223, 223, 159); /* 223, 223, 159 */
    fire_palette.data[35] = JO_COLOR_RGB(239, 239, 199); /* 239, 239, 199 */
    fire_palette.data[36] = JO_COLOR_White;


    fire = jo_software_renderer_create(fire_width, fire_height, JO_SPRITE_SCREEN);
    jo_software_renderer_clear(fire, JO_COLOR_Transparent);
    jo_sprite_set_palette(fire_palette.id);
    /* Draw a line of white pixels from which the fire effect will emerge from */
    for (int i=0; i<fire_width; i++) {
        fire->color_buffer[i + (fire_height-1) * fire->vram_size.width] = 36;
    }
}

/* Deallocate VDP1 memory allocated when starting the
 * title introduction.
 */
void
title_stop(game_action_t exit_state)
{
    jo_software_renderer_free(fire);
}

void
do_fire()
{
    for (int x=0; x<fire_width; x++) {
        for (int y=1; y<fire_height; y++) {
            spread_fire(y * fire_width + x);
        }
    }
}

void
spread_fire(int from)
{
    int to = from - fire_width;
    fire->color_buffer[to] = fire->color_buffer[from] - 1;
}

/* Update fire animation. Call repeatedly between screen
 * updates until all fire has extinguished.
 *
 * Returns updated game state.
 */
game_action_t
title_ticker()
{
    do_fire();
    /* Indicate more updates are required */
    return GA_Nothing;
}

