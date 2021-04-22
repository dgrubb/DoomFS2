/*
 * File: menu_main.h
 * Author: dgrubb
 * Date: 18/04/2021
 * Description:
 *      Implements the state handling for the
 *      main menu.
 */

#ifndef MENU_MAIN_H
#define MENU_MAIN_H

#include "defines.h"

void menu_draw();
void menu_start();
void menu_stop(game_action_t exit_state);
game_action_t menu_ticker();

/* Worker functions */

/*
void game_doom_main();
game_action_t game_inner_loop(void(*start)(void), void(*stop)(game_action_t), game_action_t(*ticker)(void), void(*drawer)(void));
void game_time_slice();
*/
/* Functions which implement portions of the
 * non-gameplay experience
 */
/*
game_action_t game_run_menu();
game_action_t game_run_title();
*/
#endif /* GAME_MAIN_H */
