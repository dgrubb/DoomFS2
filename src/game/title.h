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

#endif /* TITLE_H */

