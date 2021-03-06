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
#include "menu/menu_main.h"
#include "menu/misc.h"
#include "renderer/renderer_main.h"
#include "game/title.h"
#include "play/setup.h"
#include "video/video.h"
#include "wad/wad_main.h"

static game_error_t error = GE_None;

/* Initial starting point for entering
 * the game engine specifically.
 *
 * Returns false if something goes wrong during
 * initialisation and sets an error.
 */
bool
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
    if (!wad_init()) {
        error = GE_WadError;
        return false;
    }

    return true;
}

/* If something went wrong setting up the game (e.g.,
 * allocating a resource, loading a file etc) then the engine
 * will still start the render loop so it can deliver a message
 * to the user infroming them what went wrong.
 */
void
game_report_error()
{
    switch (error)
    {
        case GE_WadError: jo_printf(3, 3, "Failed to load WAD"); break;
        case GE_None: /* Intentional fall-through */
        default:
            jo_printf(3, 3, "No errors reported");
    }
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
    return game_inner_loop(menu_start, menu_stop, menu_ticker, menu_draw);
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
