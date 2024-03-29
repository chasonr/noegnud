#ifndef _NOEGNUD_EXTERN_H_
#define _NOEGNUD_EXTERN_H_

#include "noegnud_gui.h"
#include "noegnud_options.h"
#include "noegnud_interface.h"
#include "noegnud_fonts.h"
#include "noegnud_tilesets.h"
#include "noegnud_collection.h"
#include "noegnud_rip.h"

/* nethack &| slashem */
extern short glyph2tile[];

/* noegnud_gui */

extern noegnud_gui_twidget *noegnud_gui_active;
extern noegnud_fonts_tfont *noegnud_gui_font;
extern noegnud_gui_twidget *noegnud_guiwidget_desktop;
extern noegnud_gui_twindow *noegnud_guiwidget_console;
extern noegnud_gui_twindow *noegnud_guiwidget_minimap;
extern noegnud_gui_twindow *noegnud_guiwidget_status;
extern noegnud_gui_twidget *noegnud_guiwidget_status_container;
extern noegnud_gui_twidget *noegnud_guiwidget_options;
#ifdef POSITIONBAR
extern noegnud_gui_twindow *noegnud_guiwidget_positionbar;
extern noegnud_gui_twidget *noegnud_guiwidget_positionbar_container;
#endif
extern noegnud_gui_twidget *noegnud_gui_grabbed;
extern noegnud_gui_twidget *noegnud_gui_mouseoverwidget;
extern int noegnud_gui_mouseoverminimap;
extern noegnud_tcollection *noegnud_gui_default_widgettheme;
extern noegnud_tcollection *noegnud_gui_default_title_active_widgettheme;
extern noegnud_tcollection *noegnud_gui_default_minimap_widgettheme;

extern int noegnud_gui_menuitem_throwreturn;

extern anything noegnud_gui_menuselect_identifier;

/* noegnud_options */

extern noegnud_tcollection *noegnud_options;

extern noegnud_optiontype_int *noegnud_options_screenwidth;
extern noegnud_optiontype_int *noegnud_options_screenheight;
extern noegnud_optiontype_int *noegnud_options_screenbpp;
extern noegnud_optiontype_int *noegnud_options_fullscreen;

extern noegnud_optiontype_int *noegnud_options_keys_options;
extern noegnud_optiontype_int *noegnud_options_keys_console;
extern noegnud_optiontype_int *noegnud_options_keys_minimap;
extern noegnud_optiontype_int *noegnud_options_keys_hidegui;

extern noegnud_optiontype_int *noegnud_options_key_repeat_delay;
extern noegnud_optiontype_int *noegnud_options_key_repeat_interval;

extern noegnud_optiontype_int *noegnud_options_key_assignment_traditional;

extern noegnud_optiontype_int *noegnud_options_variant_delay;

extern noegnud_optiontype_int *noegnud_options_input_3dmouse;
extern noegnud_optiontype_int *noegnud_options_input_mouse_3d_light;
extern noegnud_optiontype_int *noegnud_options_input_mouse_gui_scrollspeed;
extern noegnud_optiontype_int *noegnud_options_interface_yn_function_windowed;
extern noegnud_optiontype_int *noegnud_options_interface_texttombstone;

extern noegnud_optiontype_int *noegnud_options_gui_window_credits_display;

extern noegnud_optiontype_int *noegnud_options_console_gap;

extern noegnud_optiontype_int *noegnud_options_gui_window_console_timestamp;
extern noegnud_optiontype_rgb
    *noegnud_options_gui_window_console_text_colour_system;
extern noegnud_optiontype_rgb
    *noegnud_options_gui_window_console_text_colour_timestamp;
extern noegnud_optiontype_rgb
    *noegnud_options_gui_window_console_text_colour_default;

extern noegnud_optiontype_string *noegnud_options_gui_text_colouring;

extern noegnud_optiontype_int *noegnud_options_mode_drawmode;

extern noegnud_optiontype_int *noegnud_options_mode_all_rotationabsolute;

extern noegnud_optiontype_string *noegnud_options_mode_tileset_tile;
extern noegnud_optiontype_float *noegnud_options_mode_tileset_iso_opacity;
extern noegnud_optiontype_int *noegnud_options_mode_tileset_halfwidth;

extern noegnud_optiontype_int *noegnud_options_mode_tileset_caverns;
extern noegnud_optiontype_int
    *noegnud_options_mode_tileset_caverns_unexplored;
extern noegnud_optiontype_int *noegnud_options_mode_tileset_caverns_cutout;

extern noegnud_optiontype_string *noegnud_options_mode_char_font;

extern noegnud_optiontype_int *noegnud_options_gui_shadow_window;
extern noegnud_optiontype_int *noegnud_options_gui_shadow_button;
extern noegnud_optiontype_float *noegnud_options_gui_shadow_opacity;

extern noegnud_optiontype_string *noegnud_options_gui_font;
extern noegnud_optiontype_string *noegnud_options_gui_texture;

extern noegnud_optiontype_int *noegnud_options_gui_widgetborder;

extern noegnud_optiontype_string *noegnud_options_minimap_font;
extern noegnud_optiontype_int *noegnud_options_minimap_visible;

extern noegnud_optiontype_int *noegnud_options_positionbar_visible;

extern noegnud_optiontype_int *noegnud_options_render_engine_fps_limit;
extern noegnud_optiontype_int *noegnud_options_render_engine_fps_show;

extern noegnud_optiontype_float *noegnud_options_render_multiplier;

extern noegnud_optiontype_float *noegnud_options_render_opengl_view_min;
extern noegnud_optiontype_float *noegnud_options_render_opengl_view_max;
extern noegnud_optiontype_float *noegnud_options_render_opengl_view_fov;

extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_zoom_default;
extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_zoom_current;
extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_zoom_delta;
extern noegnud_optiontype_float *noegnud_options_render_opengl_view_zoom_min;
extern noegnud_optiontype_float *noegnud_options_render_opengl_view_zoom_max;

extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_angle_y_default;
extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_angle_y_current;
extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_angle_y_min;
extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_angle_y_max;

extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_angle_x_default;
extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_angle_x_current;
extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_angle_x_min;
extern noegnud_optiontype_float
    *noegnud_options_render_opengl_view_angle_x_max;

extern noegnud_optiontype_int *noegnud_options_render_opengl_lighting_method;

extern noegnud_optiontype_int *noegnud_options_render_opengl_mipmapping;

extern noegnud_optiontype_int *noegnud_options_opengl_texture_max;

extern noegnud_optiontype_int *noegnud_options_render_features_autocentre;
extern noegnud_optiontype_int
    *noegnud_options_render_features_autocentre_xonly;
extern noegnud_optiontype_int
    *noegnud_options_render_features_autocentre_mouse;

extern noegnud_optiontype_int *noegnud_options_render_features_autoface;

extern noegnud_optiontype_int
    *noegnud_options_render_features_cardboardcutout;

extern noegnud_optiontype_int
    *noegnud_options_render_features_cardboardcutout_raise_monsters;
extern noegnud_optiontype_int
    *noegnud_options_render_features_cardboardcutout_raise_objects;
extern noegnud_optiontype_int
    *noegnud_options_render_features_cardboardcutout_raise_walls;

extern noegnud_optiontype_float *
    noegnud_options_render_features_cardboardcutout_wall_translucency_default;
extern noegnud_optiontype_float *
    noegnud_options_render_features_cardboardcutout_wall_translucency_current;

extern noegnud_optiontype_float
    *noegnud_options_render_features_cardboardcutout_wall_height;
extern noegnud_optiontype_float
    *noegnud_options_render_features_cardboardcutout_hole_depth;
extern noegnud_optiontype_float
    *noegnud_options_render_features_cardboardcutout_liquid_depth;

extern noegnud_optiontype_int *noegnud_options_render_bullettime_trigger;
extern noegnud_optiontype_int *noegnud_options_fun_recording_ask;

extern noegnud_optiontype_float
    *noegnud_options_render_highlight_strobe_speed;
extern noegnud_optiontype_float
    *noegnud_options_render_highlight_block_opacity;

extern noegnud_optiontype_string *noegnud_options_language;

/* noegnud_interface */

extern int noegnud_graphics_system_ready;
extern GLfloat noegnud_nethackcolours[16][4];

extern int noegnud_clip_x;
extern int noegnud_clip_y;

extern noegnud_tmap_cell noegnud_map[MAX_MAP_X][MAX_MAP_Y];

extern noegnud_fonts_tfont *noegnud_font_minimap;
extern noegnud_fonts_tfont *noegnud_font_map;

extern noegnud_glfuncs_timage *noegnud_image_dungeon;
extern noegnud_glfuncs_timage *noegnud_image_tilenotfound;

/* noegnud_render */

// extern int noegnud_render_drawmode;
extern float noegnud_render_highlight_strobe;

extern int noegnud_render_bullettime_busy;
extern int noegnud_render_bullettime_lastevent;
extern float noegnud_render_bullettime_angle;

extern float noegnud_render_middle_x;
extern float noegnud_render_middle_y;

extern float noegnud_render_offset_x;
extern float noegnud_render_offset_y;

extern int noegnud_render_selection_busy;

extern int noegnud_render_rendergui;

extern int noegnud_render_mouse_map_x;
extern int noegnud_render_mouse_map_y;

/* noegnud_glfuncs */
extern int noegnud_glfuncs_maximum_texturesize;

/* noegnud_tilesets */

extern ts_tileset *noegnud_activetileset;

/* noegnud_typeloader */

extern char noegnud_typeloader_IFS;

/* noegnud_mem */
extern int noegnud_mem_lock;

#ifdef NOEGNUDDEBUG

/* noegnud_debug */

extern int noegnud_debug_mem_memused;
extern int noegnud_debug_mem_mostmemused;
extern noegnud_tcollection *noegnud_debug_mem_ptrsizemap;

#endif

/* noegnud_reference */

extern noegnud_tcollection *noegnud_reference;
extern int noegnud_reference_tile_amount;

#endif //_NOEGNUD_EXTERN_H_
