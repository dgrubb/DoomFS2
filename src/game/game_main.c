/*
 * File: game_main.c
 * Author: dgrubb
 * Date: 23/03/2021
 * Description:
 *      Implements the main state handling for the
 *      game loop.
 */

/* Engine include */
#include <jo/jo.h>

/* Game source */
#include "defines.h"
#include "game/game_main.h"
#include "game/title.h"
#include "hud/stuff.h"
#include "menu/misc.h"
#include "renderer/renderer_main.h"
#include "game/title.h"
#include "play/setup.h"
#include "video/video.h"

/* Initial starting point for entering
 * the game engine specifically.
 *
 * Never returns.
 */
void
game_doom_main()
{
    /* Initialise Jo engine */
    jo_core_init(JO_COLOR_Black);
    jo_core_enable_reset();

    /* Initialise sub-systems */
    video_init();
    menu_load_defaults();
    menu_init();
    renderer_init();
    play_init();
    hud_init();

    /*
    while (1) {
        if (game_run_title() != GA_Exit) {
        }

        do {} while (game_run_menu() != GA_Timeout);
    }
    */
}

/* Displays the menu to the user,
 * executed by an inner render loop.
 *
 * Returns with a state when completed.
 */
game_action_t
game_run_menu()
{
    return GA_Exit;
}

/* Displays the initial introduction effects,
 * executed by an inner render loop.
 *
 * Returns with a state when completed.
 */
game_action_t
game_run_title()
{
    return game_inner_loop(title_start, title_stop, title_ticker, title_draw);
}

/* Runs a small render loop which executes the non-gameplay
 * experiences (e.g., menu, title screen etc).
 *
 * Returns with a state when completed.
 */
game_action_t
game_inner_loop(void(*start)(void), void(*stop)(int), int(*ticker)(void), void(*drawer)(void))
{
    game_action_t exit;

    /* Perform scene setup, cache graphics, etc */
    start();

    /* TODO: Read buttons */

    /* Update state, exit if scene has completed execution */
    exit = ticker();
    if (GA_Nothing != exit) break;

    /* Perform render updates */
    drawer();

    /* Teardown scene */
    stop(exit);

    return exit;
}
