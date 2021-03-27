/*
 * File: game_main.c
 * Author: dgrubb
 * Date: 23/03/2021
 * Description:
 *      Implements the main state handling for the
 *      game loop.
 */

#include "hud/stuff.h"
#include "menu/misc.h"
#include "play/setup.h"
#include "renderer/renderer_main.h"
#include "video/video.h"

void
game_doom_main()
{
    /* Initialise sub-systems */
    video_init();
    menu_load_defaults();
    menu_init();
    renderer_init();
    play_init();
    hud_init();
}
