/*
 * File: game_main.h
 * Author: dgrubb
 * Date: 23/03/2021
 * Description:
 *      Implements the main state handling for the
 *      game loop.
 */

#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include "defines.h"

/* Worker functions */
bool game_doom_main();
void game_report_error();
game_action_t game_inner_loop(void(*start)(void), void(*stop)(game_action_t), game_action_t(*ticker)(void), void(*drawer)(void));
void game_time_slice();

/* Functions which implement portions of the
 * non-gameplay experience
 */
game_action_t game_run_menu();
game_action_t game_run_title();

#endif /* GAME_MAIN_H */
