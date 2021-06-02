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
bool
wad_init()
{
    /* Open WAD file and parse its info table */
    jo_fs_cd(FILE_PSXDOOM_DIR);
    if (!jo_fs_open(&psx_doom_wad_fs, FILE_PSXDOOM_WAD)) {
        return false;
    }
    char* buffer = jo_malloc(sizeof(wadinfo_t));
    if (JO_NULL == buffer) {
        return false;
    }
    /* Reset back to the root directory */
    jo_fs_cd(JO_PARENT_DIR);

    /* Load the WAD file info block to validate */
    if (0 == jo_fs_read_next_bytes(&psx_doom_wad_fs, buffer, sizeof(wadinfo_t))) {
        /* Reading reached end of file, which shouldn't happen here */
        return false;
    }

    /* Read the first four bytes of the target file to validate it's
     * the main content WAD needed to start the game
     */
    for (int i=0; i<4; i++) {
        if (((wadinfo_t*)buffer)->id[i] != wad_header_id[i]) {
            return false;
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

    return true;
}

/* Looks up the index of a lump by its
 * name. Returns -1 if not found.
 */
int
wad_get_lump_by_id(char* id)
{
    char        name[12];
    int         first_four_bytes, second_four_bytes;
    lumpinfo_t* lump_ptr;

    jo_memset(name, 0, sizeof(name));
    for (int i=0; i<8; i++) {
        name[i] = id[i];
    }

    lump_ptr = psx_doom_wad_lumpinfo + psx_doom_wad_numlumps;
    first_four_bytes = *(int*)name;
    second_four_bytes = *(int*)&name[4];

    /* The name string will always have a maximum of 8 characters, or
     * 64 bits. Target architecture is 32 bit so, as an non-portable
     * optimisation, the two halves of the string can be converted into
     * two integers. Comparing two integers is far less costly than iterating
     * over the eight characters and comapring each one in turn a byte at
     * a time.
     */
    while (lump_ptr != psx_doom_wad_lumpinfo) {
        /* N.b., the first bit of the first byte is masked out */
        if (*(int*)&lump_ptr->name[4] == second_four_bytes && (*(int*)lump_ptr->name & 0x7F) == first_four_bytes) {
            return lump_ptr - psx_doom_wad_lumpinfo;
        }
    }

    return -1;
}

/* Loads a lump into memory assigned for
 * caching content. Returns pointer or
 * NULL on error.
 */
char*
wad_cache_lump(int lump, bool decode)
{
    int size;
    lumpcache_t *cache;

    if (psx_doom_wad_numlumps <= lump) {
        return JO_NULL;
    }

    cache = &psx_doom_wad_lumpcache[lump];
    if (!cache->cache) {

        // TODO: Other engine has two ways of deducing how much memory
        // to alloc. Should investigate further, but this implements
        // the initial path - DAG
        cache->cache = jo_malloc(psx_doom_wad_lumpinfo[lump].size);
        wad_read_lump(lump, cache->cache);

        if (psx_doom_wad_lumpinfo[lump].name[0] & 0x80 == 0) {
            psx_doom_wad_lumpencode[lump] = 1;
        } else {
            // TODO: figure out exactly what goes on here - DAG
        }
    }

    return cache->cache;
}
