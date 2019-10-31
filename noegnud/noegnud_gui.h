#ifndef _NOEGNUD_GUI_H_
#define _NOEGNUD_GUI_H_

#define NOEGNUD_GUI_WIDGET 0x01
#define NOEGNUD_GUI_WINDOW 0x02
#define NOEGNUD_GUI_TEXT 0x03
#define NOEGNUD_GUI_BUTTON 0x04
#define NOEGNUD_GUI_VSCROLL 0x05
#define NOEGNUD_GUI_MENUITEM 0x06
#define NOEGNUD_GUI_GLYPH 0x07
#define NOEGNUD_GUI_PROGRESSBAR 0x08
#define NOEGNUD_GUI_TITLEBAR 0x09

#define NOEGNUD_GUI_MAX 0x09

#define NOEGNUD_GUI_BORDER_SIZE 8

#include "noegnud_glfuncs.h"
#include "noegnud_fonts.h"
#include "noegnud_collection.h"

#include "hack.h"

void noegnud_gui_init(void);

int noegnud_gui_get_fontwidth(void);
int noegnud_gui_get_fontheight(void);

typedef struct _noegnud_gui_twidget noegnud_gui_twidget;

typedef void noegnud_gui_kill_widget_proc(noegnud_gui_twidget *widget);
typedef void noegnud_gui_draw_widget_proc(noegnud_gui_twidget *widget,
                                          int drawchildren);
typedef void noegnud_gui_autosize_widget_proc(noegnud_gui_twidget *widget);
typedef void noegnud_gui_event_widget_proc(noegnud_gui_twidget *widget,
                                           SDL_Event *event);

void noegnud_gui_draw_null(noegnud_gui_twidget *widget, int drawchildren);

struct _noegnud_gui_twidget {
    int type;

    noegnud_gui_twidget *parent;
    noegnud_gui_twidget *prevsibling;
    noegnud_gui_twidget *nextsibling;
    noegnud_gui_twidget *child;

    noegnud_gui_twidget *clipto;

    int x, y;
    int offset_x, offset_y;
    int width, height;

    GLfloat r, g, b, a;

    int mouseover_check;
    int mouseover;

    noegnud_tcollection *theme;

    noegnud_gui_twidget *vscrollwidget;
    noegnud_gui_twidget *hscrollwidget;

    int vscroll, hscroll;
    int vscroll_pos, hscroll_pos;
    int autocentre;

    noegnud_gui_draw_widget_proc *draw;
    noegnud_gui_autosize_widget_proc *autosize;
    noegnud_gui_kill_widget_proc *kill;
    noegnud_gui_event_widget_proc *event;
};

#define noegnud_gui_tvslider noegnud_gui_twindow

noegnud_gui_twidget *noegnud_gui_create_widget(noegnud_gui_twidget *parent,
                                               int x, int y, int width,
                                               int height, int datasize);

void noegnud_gui_draw_widget(noegnud_gui_twidget *widget, int drawchildren);
void noegnud_gui_event_null(noegnud_gui_twidget *widget, SDL_Event *event);

void noegnud_gui_widget_addchikillld(noegnud_gui_twidget *widget,
                                     noegnud_gui_twidget *child);
void noegnud_gui_kill_widget_relatives(noegnud_gui_twidget *widget);

// -------------------------------------------------------- WINDOW

typedef struct { // inherits from widget
    noegnud_gui_twidget widget;
    noegnud_glfuncs_timage *image;
    noegnud_gui_twidget *tomove;
    noegnud_gui_twidget *titlebar;
    int localimage;
    int autoresize;
    int rip;
    int rip_how;
    int image_tiled;
    int movable;
    int movement_lock_x;
    int refreshtitlebar;
} noegnud_gui_twindow;

noegnud_gui_twindow *noegnud_gui_create_window(noegnud_gui_twidget *parent,
                                               int x, int y, int width,
                                               int height, GLfloat r,
                                               GLfloat g, GLfloat b,
                                               GLfloat a, int datasize);
void noegnud_gui_draw_window(noegnud_gui_twindow *window, int drawchildren);
void noegnud_gui_event_window(noegnud_gui_twindow *window, SDL_Event *event);

// -------------------------------------------------------- TEXT

typedef struct {
    noegnud_gui_twidget widget;
    GLfloat r, g, b;
    char *text;
    noegnud_fonts_tfont *font;
    int dynamiccharwidth;
} noegnud_gui_ttext;

noegnud_gui_ttext *noegnud_gui_create_text(noegnud_gui_twidget *parent, int x,
                                           int y, int width, int height,
                                           GLfloat r, GLfloat g, GLfloat b,
                                           const char *text);

// -------------------------------------------------------- BUTTON

typedef struct { // inherits from window
    noegnud_gui_twindow window;
    noegnud_gui_ttext *text;
    int accelerator;
} noegnud_gui_tbutton;

noegnud_gui_tbutton *noegnud_gui_create_button(
    noegnud_gui_twidget *parent, int x, int y, int width, int height,
    GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat tr, GLfloat tg,
    GLfloat tb, char *string, int accelerator);

// -------------------------------------------------------- TEXTBUTTON

noegnud_gui_tbutton *noegnud_gui_create_textbutton(
    noegnud_gui_twidget *parent, int x, int y, GLfloat r, GLfloat g,
    GLfloat b, GLfloat a, GLfloat tr, GLfloat tg, GLfloat tb, char *string,
    char accelerator);

// -------------------------------------------------------- GLYPH

typedef struct {
    noegnud_gui_twidget widget;
    int glyph;
    noegnud_gui_twidget *activepopup;
} noegnud_gui_tglyph;

// -------------------------------------------------------- VSLIDER

typedef struct {
    noegnud_gui_twidget widget;
} noegnud_gui_tvscroll;

// -------------------------------------------------------- MENUITEM

typedef struct {
    // noegnud_gui_twidget widget;
    noegnud_gui_twindow window;
    ;
    GLfloat r, g, b, a;
    anything identifier;
    char ch;
    char gch;
    int selected;
    int highlighted;
    char *text;
} noegnud_gui_tmenuitem;

// --------------------------------------------------------

void noegnud_gui_nh_putstr(noegnud_gui_twindow *window, const char *text,
                           GLfloat r, GLfloat g, GLfloat b);
void noegnud_gui_add_actionbutton(noegnud_gui_twindow *window,
                                  const char *text, char accelerator);

void noegnud_gui_nh_addmenu(noegnud_gui_twindow *window, anything identifier,
                            int glyph, char ch, char gch, const char *text,
                            int selected);
void noegnud_gui_nh_addmenu_menuitem_addaccelerator(
    noegnud_gui_twidget *menuitem, char ch);

noegnud_gui_twidget *noegnud_gui_nh_yn_function(const char *question,
                                                const char *choices,
                                                char def);
noegnud_gui_twidget *noegnud_gui_nh_getlin(const char *ques,
                                           const char *input);

void noegnud_gui_inconsole_noegnudtext(noegnud_gui_twidget *widget,
                                       const char *text, int dynamic,
                                       GLfloat r, GLfloat g, GLfloat b);

void noegnud_gui_reshuffle_console_children(noegnud_gui_twidget *widget);

void noegnud_gui_draw_minimap(noegnud_gui_twindow *window, int drawchildren);
void noegnud_gui_event_minimap(noegnud_gui_twidget *map, SDL_Event *event);

int noegnud_gui_widget_getabsolute_x(noegnud_gui_twidget *widget);
int noegnud_gui_widget_getabsolute_y(noegnud_gui_twidget *widget);

/* lookup between window ID and window pointer */
void noegnud_gui_free_winid(winid window);
noegnud_gui_twindow *noegnud_gui_winid_to_window(winid window);
winid noegnud_gui_window_to_winid(noegnud_gui_twindow *window);

#endif // _NOEGNUD_GUI_H_
