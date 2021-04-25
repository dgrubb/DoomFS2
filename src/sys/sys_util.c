/*
 * File: sys_util.h
 * Author: dgrubb
 * Date: 23/04/2021
 * Description:
 *      Provides intermediary functions which are platform specific.
 */

#include <jo/jo.h>

/* Copies image data from a WAD lump into
 * a specifified location in VRAM.
 */
bool
sys_load_image(char* vram, char* id, int lump)
{
    if (id) {
        lump = wad_get_lump_by_id(id);
    }
    if (-1 == lump) {
        return false;
    }



    return true;
}

/* Copies image data from a WAD lump into
 * a specified location in VRAM when requested
 * by name.
 */
bool
sys_load_image_by_id(char* vram, char* id)
{
    return sys_load_image(vram, id, 0);
}

/* Copies image data from a WAD lump into
 * a specified location in VRAM when requested
 * by lump index.
 */
bool
sys_load_image_by_lump_idx(char* vram, int lump)
{
    return sys_load_image(vram, JO_NULL, lump);
}
