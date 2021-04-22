/*
 * File: wad_main.c
 * Author: dgrubb
 * Date: 18/04/2021
 * Description:
 *      Provides utilities for handling WAD format
 *      archives.
 */

#include <jo/jo.h>
#include "defines.h"
#include "wad/wad_main.h"

/* Four byte identifier found at the start of
 * official WAD files.
 */
const char wad_header_id[] = "IWAD";

/* File handle for the main WAD file containing all the
 * game data.
 */
static jo_file      psx_doom_wad_fs;
static int          psx_doom_wad_numlumps;
static lumpinfo_t*  psx_doom_wad_lumpinfo;
static int          psx_doom_wad_infotable;
static lumpcache_t* psx_doom_wad_lumpcache;
static char*        psx_doom_wad_lumpencode;

/* Loads the main content WAD file containing
 * the port specific data
 */
void
wad_init()
{
    /* Open WAD file and parse its info table */
    jo_fs_cd(FILE_PSXDOOM_DIR);
    if (!jo_fs_open(&psx_doom_wad_fs, FILE_PSXDOOM_WAD)) {
        return;
    }
    char* buffer = jo_malloc(sizeof(wadinfo_t));
    if (JO_NULL == buffer) {
        return;
    }
    /* Reset back to the root directory */
    jo_fs_cd(JO_PARENT_DIR);

    /* Load the WAD file info block to validate */
    if (0 == jo_fs_read_next_bytes(&psx_doom_wad_fs, buffer, sizeof(wadinfo_t))) {
        /* Reading reached end of file, which shouldn't happen here */
        return;
    }

    /* Read the first four bytes of the target file to validate it's
     * the main content WAD needed to start the game
     */
    for (int i=0; i<4; i++) {
        if (((wadinfo_t*)buffer)->id[i] != wad_header_id[i]) {
            return;
        }
    }

    /* Load information from the WAD about its lump directory */
    psx_doom_wad_numlumps = ((wadinfo_t*)buffer)->num_lumps;
    psx_doom_wad_lumpinfo = (lumpinfo_t*)jo_malloc(psx_doom_wad_numlumps * sizeof(lumpinfo_t));
    psx_doom_wad_infotable = ((wadinfo_t*)buffer)->info_table;

    /* Allocate temporary memory to be used later for caching
     * lumps as they're loaded dynamically
     */
    psx_doom_wad_lumpcache = (lumpcache_t*)jo_malloc(psx_doom_wad_numlumps * sizeof(lumpcache_t));
    psx_doom_wad_lumpencode = (char*)jo_malloc(psx_doom_wad_numlumps);
}
