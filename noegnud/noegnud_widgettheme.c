#include "noegnud_config.h"
#include "noegnud_mem.h"
#include "noegnud_collection.h"
#include "noegnud_options.h"
#include "noegnud_typeloader.h"
#include "noegnud_common.h"
#include "noegnud_widgettheme.h"
#include "noegnud_gui.h"

static noegnud_tcollection *noegnud_widgetthemes = NULL;

static int noegnud_widgettheme_startup(void);
static void noegnud_widgettheme_done(void);

static void
noegnud_widgettheme_done(void)
{
    noegnud_collection_destroy(&noegnud_widgetthemes);
}

static void
destroy_segment(void *segment_)
{
    noegnud_widgettheme_tsegment *segment = (noegnud_widgettheme_tsegment *) segment_;

    noegnud_glfuncs_unloadimage(segment->image);
    noegnud_mem_free(segment);
}

static void
destroy_inner(void *inner_)
{
    noegnud_tcollection *inner = (noegnud_tcollection *) inner_;
    noegnud_collection_destroy(&inner);
}

static int
noegnud_widgettheme_startup(void)
{
    noegnud_widgetthemes = NULL;
    return 1;
}

void
noegnud_widgettheme_init(void)
{
    printf("* initialising widgetthemes\n");

    if (noegnud_widgettheme_startup())
        atexit(noegnud_widgettheme_done);
}

static int noegnud_widgettheme_load_parser_counter = 1;
static void
noegnud_widgettheme_load_parser(char *setting, int nparams, char *params,
                                void *data)
{
    noegnud_tcollection **widgettheme;
    noegnud_widgettheme_tsegment *segment;
    char filename[2048];

    char *eachparam;

    if (!strcmp(setting, "$include$")) {
        noegnud_widgettheme_load(params);
        return;
    }

    widgettheme = data;

    if (!strcmp(setting, "segment")) {
        if (nparams == (1 + 3 * 2 + 3 * 2 + 2)) {
            eachparam = params;
            segment =
                noegnud_mem_malloc(sizeof(noegnud_widgettheme_tsegment));

            while (*eachparam++)
                ;

            segment->start.parent_alignment.x = atof(eachparam);
            while (*eachparam++)
                ;
            segment->start.parent_alignment.y = atof(eachparam);
            while (*eachparam++)
                ;
            segment->start.segment_relative_offset.x = atof(eachparam);
            while (*eachparam++)
                ;
            segment->start.segment_relative_offset.y = atof(eachparam);
            while (*eachparam++)
                ;
            segment->start.pixel_offset.x = atof(eachparam);
            while (*eachparam++)
                ;
            segment->start.pixel_offset.y = atof(eachparam);
            while (*eachparam++)
                ;

            segment->end.parent_alignment.x = atof(eachparam);
            while (*eachparam++)
                ;
            segment->end.parent_alignment.y = atof(eachparam);
            while (*eachparam++)
                ;
            segment->end.segment_relative_offset.x = atof(eachparam);
            while (*eachparam++)
                ;
            segment->end.segment_relative_offset.y = atof(eachparam);
            while (*eachparam++)
                ;
            segment->end.pixel_offset.x = atof(eachparam);
            while (*eachparam++)
                ;
            segment->end.pixel_offset.y = atof(eachparam);
            while (*eachparam++)
                ;

            segment->tiled_x = (atoi(eachparam) != 0);
            while (*eachparam++)
                ;
            segment->tiled_y = (atoi(eachparam) != 0);

            sprintf(filename, "widgetthemes/%s", params);
            segment->image = noegnud_glfuncs_loadimage(
                filename, 0, segment->tiled_x || segment->tiled_y, 0);

            sprintf(filename, "segment: %d",
                    noegnud_widgettheme_load_parser_counter);

            if (*widgettheme) {
                noegnud_collection_add(*widgettheme, filename, segment,
                                       destroy_segment);
            } else {
                *widgettheme = noegnud_collection_create(filename, segment,
                                                         destroy_segment);
            }

        } else {
            printf("[WIDGETTHEME] syntax error parsing widget info file.\n");
        }
    }

    noegnud_widgettheme_load_parser_counter++;
}

noegnud_tcollection *
noegnud_widgettheme_load(const char *filename)
{
    noegnud_tcollection *widgettheme;
    char *szHomedir;
    char physical_filename[2048];

    if ((widgettheme =
             noegnud_collection_data(noegnud_widgetthemes, filename))) {
        printf("[WIDGETTHEME] noegnud_widgettheme_load: cached file found "
               "\"%s\"\n",
               filename);
        return widgettheme;
    }

    szHomedir = noegnud_options_get_home();
    sprintf(physical_filename, "%s/widgetthemes/%s.theme",
            szHomedir, filename);
    noegnud_mem_free(szHomedir);
    if (!noegnud_common_file_exists(physical_filename))
        sprintf(physical_filename,
                "../" NOEGNUD_DATADIR "/widgetthemes/%s.theme", filename);
    if (!noegnud_common_file_exists(physical_filename)) {
        printf(
            "[WIDGETTHEME] noegnud_widgettheme_load: file not found \"%s\"\n",
            filename);
        return NULL;
    }

    printf("[WIDGETTHEME] noegnud_widgettheme_load: loading \"%s\"  (%s)\n",
           filename, physical_filename);

    widgettheme = NULL;
    noegnud_typeloader_IFS = ',';
    noegnud_typeloader_parsefile(noegnud_widgettheme_load_parser,
                                 physical_filename, &widgettheme);

    if (widgettheme) {
        if (!noegnud_widgetthemes) {
            noegnud_widgetthemes =
                noegnud_collection_create(filename, widgettheme,
                                          destroy_inner);
        } else {
            noegnud_collection_add(noegnud_widgetthemes, filename,
                                   widgettheme, destroy_inner);
        }
    } else {
        printf("[WIDGETTHEME] warning: empty theme \"%s\" (%s).\n", filename,
               physical_filename);
    }

    return widgettheme;
}

void
noegnud_widgettheme_draw(noegnud_gui_twidget *widget,
                         noegnud_tcollection *theme)
{
    float x1, y1, x2, y2, txd, tyd;

    noegnud_widgettheme_tsegment *segment;
    while (theme) {
        segment = theme->data;

        x1 = noegnud_gui_widget_getabsolute_x(widget)
             + (segment->start.parent_alignment.x + 1) * (float) widget->width
                   / 2
             + (segment->start.segment_relative_offset.x
                * (float) segment->image->width)
             + (segment->start.pixel_offset.x);
        y1 = noegnud_gui_widget_getabsolute_y(widget)
             + (segment->start.parent_alignment.y + 1) * widget->height / 2
             + (segment->start.segment_relative_offset.y
                * (float) segment->image->block[0][0]->height)
             + (segment->start.pixel_offset.y);

        x2 = noegnud_gui_widget_getabsolute_x(widget)
             + (segment->end.parent_alignment.x + 1) * widget->width / 2
             + (segment->end.segment_relative_offset.x
                * (float) segment->image->width)
             + (segment->end.pixel_offset.x);
        y2 = noegnud_gui_widget_getabsolute_y(widget)
             + (segment->end.parent_alignment.y + 1) * widget->height / 2
             + (segment->end.segment_relative_offset.y
                * (float) segment->image->block[0][0]->height)
             + (segment->end.pixel_offset.y);

        if (!segment->tiled_x) {
            txd = segment->image->block[0][0]->fx2;
        } else {
            txd = segment->image->block[0][0]->fx1
                  + (segment->image->block[0][0]->fx2
                     - segment->image->block[0][0]->fx1)
                        * (((float) (x2 - x1))
                           / ((float) segment->image->block[0][0]->width));
        }
        if (!segment->tiled_y) {
            tyd = segment->image->block[0][0]->fy1;
        } else {
            tyd = segment->image->block[0][0]->fy2
                  + ((segment->image->block[0][0]->fy1
                      - segment->image->block[0][0]->fy2)
                     * (((float) (y2 - y1))
                        / ((float) segment->image->block[0][0]->height)));
        }

        y1 = noegnud_options_screenheight->value - y1;
        y2 = noegnud_options_screenheight->value - y2;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, segment->image->block[0][0]->image);
        glBegin(GL_QUADS);
        glColor4f(widget->r, widget->g, widget->b, widget->a);
        glTexCoord2f(segment->image->block[0][0]->fx1,
                     segment->image->block[0][0]->fy2);
        glVertex2i(x1, y2);
        glTexCoord2f(txd, segment->image->block[0][0]->fy2);
        glVertex2i(x2, y2);
        glTexCoord2f(txd, tyd);
        glVertex2i(x2, y1);
        glTexCoord2f(segment->image->block[0][0]->fx1, tyd);
        glVertex2i(x1, y1);
        glEnd();

        theme = theme->next;
    }
}
