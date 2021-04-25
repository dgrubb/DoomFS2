/*
 * File: sys_util.c
 * Author: dgrubb
 * Date: 23/04/2021
 * Description:
 *      Provides intermediary functions which are platform specific.
 */

#ifndef SYS_UTIL_H
#define SYS_UTIL_H

bool sys_load_image(char* vram, char* id, int lump);
bool sys_load_image_by_id(char* vram, char* id);
bool sys_load_image_by_lump_idx(char* vram, int lump);

#endif /* SYS_UTIL_H */
