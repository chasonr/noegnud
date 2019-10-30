#ifndef _NOEGNUD_INTERFACE_H_
#define _NOEGNUD_INTERFACE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "hack.h"
#include "dlb.h"

#include "noegnud_options.h"

#define boolean int

#define MAX_MAP_X (80 - 1)
#define MAX_MAP_Y (22 - 1)

typedef struct {
    int glyph_primary;
    int glyph_back, glyph_middle, glyph_fore;
    unsigned special_primary;
    unsigned special_fore, special_middle, special_back;
    int colour_primary;
    int colour_fore, colour_middle, colour_back;
    int ch_primary;
    int ch_back, ch_middle, ch_fore;
    int tile_primary;
    int tile_back, tile_middle, tile_fore;
    int low, high, translucent;
} noegnud_tmap_cell;

extern noegnud_optiontype_int *noegnud_screenwidth;
extern noegnud_optiontype_int *noegnud_screenheight;
extern noegnud_optiontype_int *noegnud_screenbpp;
extern noegnud_optiontype_int *noegnud_fullscreen;

void noegnud_end_menu(winid window, const char *prompt);
#ifdef CHANGE_COLOR /* the Mac uses a palette device */
void noegnud_change_color(void);
#ifdef MAC
void noegnud_change_background(void);
void set_noegnud_font_name(void);
#endif
void noegnud_get_color_string(void);
#endif

#endif /* _NOEGNUD_INTERFACE_H_ */
