/*
 * File: wad_main.h
 * Author: dgrubb
 * Date: 18/04/2021
 * Description:
 *      Provides utilities for handling WAD format
 *      archives.
 */

#ifndef WAD_MAIN_H
#define WAD_MAIN_H

#include "defines.h"

bool wad_init();
int wad_get_lump_by_id(char* name);
char* wad_cache_lump(int lump, bool decode);

#endif /* WAD_MAIN_H */
