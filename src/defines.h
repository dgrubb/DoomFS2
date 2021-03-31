/*
 * File: defines.h
 * Author: dgrubb
 * Date: 30/03/2021
 * Description:
 *      Provides definitions for game specific events, data, and
 *      types.
 */

#ifndef DEFINES_H
#define DEFINES_H

/* Basic state machine states the game
 * can be in.
 */
typedef enum
{
    GS_Title,
    GS_Menu,
    GS_Play
} game_state_t;

/* Specifies top-level events for
 * traversing through the game logic.
 */
typedef enum
{
    GA_Nothing,
    GA_Died,
    GA_Completed,
    GA_SecretExit,
    GA_Warped,
    GA_ExitDemo,
    GA_Timeout,
    GA_Restart,
    GA_Exit
} game_action_t;

#endif /* DEFINES_H */
