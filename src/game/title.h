/*
 * File: title.h
 * Author: dgrubb
 * Date: 30/03/2021
 * Description:
 *      Implements the main introductory effect.
 */

#ifndef TITLE_H
#define TITLE_H

#include "defines.h"

void title_draw();
void title_start();
void title_stop(game_action_t exit_state);
game_action_t title_ticker();
void title_draw_fire();
void title_extinguish_fire();
void title_update_fire(int origin);

#endif /* TITLE_H */
