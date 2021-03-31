/*
 * File: title.c
 * Author: dgrubb
 * Date: 30/03/2021
 * Description:
 *      Implements the main introductory effect.
 */

#include "game/title.h"

void
title_draw()
{
}

void
title_start()
{
}

void
title_stop(game_action_t exit_state)
{
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

