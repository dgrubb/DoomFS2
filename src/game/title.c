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

bool notyet = true;

const jo_color fire_palette_test[] = {
    JO_COLOR_Transparent, /* Transparent */
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

int
get_palette_idx(jo_color color)
{
    int i=0;
    for (i=0; i<37; i++) {
        if (color == fire_palette_test[i]) {
            return i;
        }
    }
    return 0;
}

/* Pointer to allocated scratch memory for drawing onto */
jo_software_renderer_gfx* fire;
const int fire_width = VIDEO_WIDTH;
const int fire_height = VIDEO_HEIGHT/4;

/* Grabs the content of the progressing fire image
 * and draws it to the correct layer on frame update.
 */
void
title_draw()
{
    jo_sprite_draw3D2(fire->sprite_id, 0, VIDEO_HEIGHT-fire_height, 500);
}

/* Allocate VDP1 memeory to use as a crude framebuffer for
 * drawing intermediary fire effect steps onto.
 */
void
title_start()
{
    fire = jo_software_renderer_create(fire_width, fire_height, JO_SPRITE_SCREEN);
    jo_software_renderer_clear(fire, JO_COLOR_Cyan);
    //jo_sprite_set_palette(fire_palette.id);
    /* Draw a line of white pixels from which the fire effect will emerge from */
    for (int i=0; i<fire_width; i++) {
        fire->color_buffer[i + (fire_height-1) * fire->vram_size.width] = JO_COLOR_White;
    }
//    jo_core_add_slave_callback(do_fire);
    notyet = false;
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
    if (notyet) return;
    for (int x=0; x<fire_width; x++) {
        for (int y=1; y<fire_height; y++) {
            spread_fire(y * fire_width + x);
        }
    }
    jo_software_renderer_flush(fire);
}

void
spread_fire(int from)
{
    int rand = jo_random(3) & 3;
    int to = from - fire_width - rand + 1;
    int idx = get_palette_idx(fire->color_buffer[from]) - (rand & 1);
    fire->color_buffer[to] = fire_palette_test[idx];
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

