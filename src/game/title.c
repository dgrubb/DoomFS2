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
    JO_COLOR_Transparent, /* Transparent */
    32771,
    32085,
    32808,
    32842,
    32876,
    32878,
    32913,
    32947,
    33013,
    33047,
    33048,
    33083,
    33115,
    33115,
    33146,
    34202,
    34233,
    34265,
    34297,
    35353,
    35352,
    35352,
    36440,
    36471,
    36471,
    37527,
    37527,
    38583,
    38582,
    38614,
    39638,
    46905,
    53115,
    58301,
    JO_COLOR_White
};

int
get_palette_idx(jo_color color)
{
    int i=0;
    for (i=0; i<36; i++) {
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
    jo_software_renderer_flush(fire);
}

void
spread_fire(int from)
{
    int rand = jo_random(3) & 3;
    fire->color_buffer[from - fire_width - rand + 1] = fire_palette_test[get_palette_idx(fire->color_buffer[from]) - (rand & 1)];
    /*
    int to = from - fire_width - rand + 1;
    fire->color_buffer[to] = fire->color_buffer[from] - (rand & 1);
    */
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

