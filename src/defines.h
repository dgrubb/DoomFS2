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

#define FILE_PSXDOOM_DIR "abin"
#define FILE_PSXDOOM_WAD "PSXDOOM.WAD"

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

/* WAD file info block, for full specification see:
 * https://doom.fandom.com/wiki/WAD
 */
typedef struct
{
    char id[4];      /* Expected to be IWAD (official game WADs), PWADS (user-created content) not supported */
    int  num_lumps;  /* Number of lumps contained in this WAD */
    int  info_table; /* Pointer to directory location */
} wadinfo_t;

typedef struct
{
    int file_pos;
    int size;
    char name[8];
} lumpinfo_t;

typedef struct
{
    void* cache;
} lumpcache_t;

#endif /* DEFINES_H */
