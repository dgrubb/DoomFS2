/*
 * File: game_main.c
 * Author: dgrubb
 * Date: 23/03/2021
 * Description:
 *      Implements the main state handling for the
 *      game loop.
 */

#include "video/video.h"

void
game_doom_main()
{
    /* Initialise sub-systems */
    video_init();
    menu_load_defaults();
    menu_init();
}
