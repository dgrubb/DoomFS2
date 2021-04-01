/*
 * File: video.c
 * Author: dgrubb
 * Date: 25/03/2021
 * Description:
 *      Provides basic access to video output.
 */

#include <jo/jo.h>

void
video_init()
{
    /* In the traditional engine this is used for allocating four (and a bit)
     * framebuffers. One framebuffer is used for most of the rendering and the
     * others are used for producing special effects such as interstitial wipes.
     * Instead, we're going to cater to the platform and generate game content
     * in VDP1's framebuffer (walls, enemies, HUD etc) and enable VDP2's
     * background layer for applying a skybox. This is roughly analagous to
     * the original engine's intent but with the added bonus of handling the
     * skybox in a hardware accelerated layer.
     */
    /* TODO: decide what is actually needed here:
    jo_set_displayed_screens(JO_NBG0_SCREEN);
    */
}
