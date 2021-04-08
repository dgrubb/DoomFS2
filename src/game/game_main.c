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
}

/* In between the rendering the game engine will execute
 * a callback to allow for the game logic to have a slice
 * of time. This is where the basic state machine will decide
 * which branch of execution to follow.
 *
 * No return value.
 */
void
game_time_slice()
{
    /* The game always starts with showing the introductory
     * fire/logo scroll. Will later transition to other states
     * dictated by the simple state machine
     */
    static game_state_t game_state = GS_Title;

    /* Walk through the game state machine */
    switch (game_state)
    {
        case GS_Menu: game_run_menu(); break;
        case GS_Play: /* TODO */; break;
        case GS_Title:
            if (GA_Nothing != game_run_title()) {
                /* Title introductory screen has finished, move onto
                 * the next state
                 */
                game_state = GS_Menu;
            }
            break;
        default: /* TODO */ break;
    }
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
game_inner_loop(void(*start)(void), void(*stop)(game_action_t), game_action_t(*ticker)(void), void(*drawer)(void))
{
    /* Storage of state in between time slices */
    static bool init = false;
    static bool finished = false;
    game_action_t exit;

    /* Perform scene setup, cache graphics, etc */
    if (!init) {
        start();
        init = true;
    }

    /* Update state, exit if scene has completed execution */
    exit = ticker();
    if (GA_Nothing != exit) finished = true;

    /* Perform render updates */
    drawer();

    /* Teardown scene, deallocate memory, reset devices etc */
    if (finished) {
        stop(exit);
        /* Reset state so the next scene
         * enters this function afresh
         */
        init = false;
        finished = false;
    }

    return exit;
}
