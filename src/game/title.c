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

/* Pointer to allocated scratch memory for drawing onto */
jo_software_renderer_gfx* fire;

/* Grabs the content of the progressing fire image
 * and draws it to the correct layer on frame update.
 */
void
title_draw()
{

}

/* Allocate VDP1 memeory to use as a crude framebuffer for
 * drawing intermediary fire effect steps onto.
 */
void
title_start()
{
    fire = jo_software_renderer_create(VIDEO_WIDTH, VIDEO_HEIGHT, JO_SPRITE_SCREEN);
}

/* Deallocate VDP1 memory allocated when starting the
 * title introduction.
 */
void
title_stop(game_action_t exit_state)
{
    jo_software_renderer_free(fire);
}

/* Update fire animation. Call repeatedly between screen
 * updates until all fire has extinguished.
 *
 * Returns updated game state.
 */
game_action_t
title_ticker()
{

    /* Indicate more updates are required */
    return GA_Exit;
}

