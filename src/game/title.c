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

/* Describes a small colour palette which extends from dark
 * brown and red hues at the bottom, up through oranges and yellows,
 * to white at the top. Simulates the heat spectrum range of fire
 */
const jo_color fire_palette[] = {
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

/* Transient object pointers */
static jo_software_renderer_gfx* fire;              /* Pointer to sprite used as scratch render surface */
static unsigned char*            fire_idx;          /* Poiner to table containing colour lookup indexes */

/* Constants */
const int   fire_width            = VIDEO_WIDTH;    /* Width of the fire sprite */
const int   fire_height           = VIDEO_HEIGHT/4; /* Height of the fire sprite */
const float fire_horizontal_scale = 1.0;            /* Horizontal scaling factor of fire sprite */
const float fire_vertical_scale   = 2.5;            /* Vertical scaling factor of fire sprite */
const int   fire_x                = 0;              /* Fire sprite X coordinate */
const int   fire_y                = 136;            /* Fire sprite Y coordinate */

/* Grabs the content of the progressing fire image
 * and draws it to the correct layer on frame update.
 */
void
title_draw()
{
    jo_sprite_draw3D2(fire->sprite_id, fire_x, fire_y, 500);
}

/* Allocate VDP1 memory to use as a crude framebuffer for
 * drawing intermediary fire effect steps onto.
 */
void
title_start()
{
    /* Allocate memory for a sprite and a table of colour lookup indexes */
    fire_idx = (unsigned char*)jo_malloc_with_behaviour((sizeof(unsigned char) * fire_width * fire_height), JO_MALLOC_TRY_REUSE_BLOCK);
    jo_printf(3, 3, "data ptr: 0x%X", fire_idx);
    jo_memset(fire_idx, 0, (sizeof(unsigned char) * fire_width * fire_height));
    fire = jo_software_renderer_create(fire_width, fire_height, JO_SPRITE_SCREEN);
    jo_software_renderer_clear(fire, JO_COLOR_Transparent);

    /* Draw a line of white pixels where the fire effect will emenate from */
    for (int i=0; i<fire_width; i++) {
        fire_idx[i + (fire_height-1) * fire_width] = 34;
    }

    /* Use hardware scaling to better fill the screen without needing to 
     * handle every pixel in software.
     */
    jo_sprite_change_sprite_scale_xy(fire_horizontal_scale, fire_vertical_scale);
}

/* Deallocate VDP1 memory allocated when starting the
 * title introduction.
 */
void
title_stop(game_action_t exit_state)
{
    jo_printf(3, 5, "sizeof: 0x%X", fire_idx);

    if (JO_NULL != fire) {
        jo_software_renderer_free(fire);
        fire = JO_NULL;
    }

    if (JO_NULL != fire_idx) {
        jo_free(fire_idx);
        fire_idx = JO_NULL;
    }
}

/* Updates the entire fire sprite with a fresh
 * appearance and copies the new drawing into 
 * proper video RAM.
 */
void
title_draw_fire()
{
    for (int x=0; x<fire_width; x++) {
        for (int y=1; y<fire_height; y++) {
            title_update_fire(y * fire_width + x);
        }
    }
    jo_software_renderer_flush(fire);
}

/* Updates a single pixel colour based on the state of its
 * nearest neighbours, with a little randomness for extra 
 * effect. Derived from algorithm detailed at:
 * https://fabiensanglard.net/doom_fire_psx/
 */
void
title_update_fire(int origin)
{
    int rand = jo_random(3) & 3;
    int destination = origin - fire_width - rand + 1;
    /* Bounds check to avoid scrubbing over memory below the first index, 
     * allocated for block descriptor
     */
    if (destination < 0) destination = 0;
    /* New colour state is updated by shifting progressively lower through the 
     * colour lookup table by a number of indexes between 1 and 3. As long as the
     * lower most strip of pixels is "white hot" the fire will burn
     */
    fire_idx[destination] = fire_idx[origin] - (rand & 1);
    fire->color_buffer[destination] = fire_palette[fire_idx[destination]];
}

/* Erases the bottom line of fire pixels so only progressively
 * lower values of shifts through the colour lookup table will
 * now occur. The visual effect will be of the flames appearing
 * to cool off and peter out.
 */
void
title_extinguish_fire()
{
    for (int i=0; i<fire_width; i++) {
        fire_idx[i + (fire_height-1) * fire_width] = 0;
    }
}

/* Update fire animation. Call repeatedly between screen
 * updates until all fire has extinguished.
 *
 * Returns updated game state.
 */
game_action_t
title_ticker()
{
    /* Update the fire animation */
    title_draw_fire();

    /* Poll inputs and exit if the user presses any action button */
    if (jo_is_pad1_available()) {
        if (jo_is_pad1_key_down(JO_KEY_A)) {
            return GA_Exit;
        }
    }

    /* Indicate more updates are required */
    return GA_Nothing;
}

