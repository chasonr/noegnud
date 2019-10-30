#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#include "noegnud_mem.h"
#include "noegnud_textcolour.h"

char *
noegnud_textcolour_rgb_pbuffer(const char *haystack,
                               struct re_pattern_buffer *needle, float br,
                               float bg, float bb, float ar, float ag,
                               float ab)
{
    int rx_pos, rx_len;
    char *szReturn = NULL;
    char *szRetch;
    unsigned char ubr, ubg, ubb, uar, uag, uab;

    if ((rx_pos = re_search(needle, haystack, strlen(haystack), 0,
                            strlen(haystack), 0))
        >= 0) {
        if ((rx_len = re_match(needle, haystack, strlen(haystack), rx_pos, 0))
            > 0) {
            szRetch = szReturn =
                noegnud_mem_malloc(strlen(haystack) + 6 + 6 + 1);

            if (rx_pos > 0) {
                strncpy(szRetch, haystack, rx_pos);
                szRetch += rx_pos;
                haystack += rx_pos;
            }

            if (br < 0)
                br = 0;
            if (bg < 0)
                bg = 0;
            if (bb < 0)
                bb = 0;
            if (ar < 0)
                ar = 0;
            if (ag < 0)
                ag = 0;
            if (ab < 0)
                ab = 0;
            if (br > 1)
                br = 1;
            if (bg > 1)
                bg = 1;
            if (bb > 1)
                bb = 1;
            if (ar > 1)
                ar = 1;
            if (ag > 1)
                ag = 1;
            if (ab > 1)
                ab = 1;

            ubr = (int) ((br * 254.0) + 1.0);
            ubg = (int) ((bg * 254.0) + 1.0);
            ubb = (int) ((bb * 254.0) + 1.0);
            uar = (int) ((ar * 254.0) + 1.0);
            uag = (int) ((ag * 254.0) + 1.0);
            uab = (int) ((ab * 254.0) + 1.0);

            *szRetch = NOEGNUD_TEXTCOLOUR_CONTROL;
            szRetch++;
            *szRetch = NOEGNUD_TEXTCOLOUR_CODE_RGB;
            szRetch++;
            *szRetch = ubr;
            szRetch++;
            *szRetch = ubg;
            szRetch++;
            *szRetch = ubb;
            szRetch++;

            strncpy(szRetch, haystack, rx_len);
            szRetch += rx_len;
            haystack += rx_len;

            if (*haystack) {
                *szRetch = NOEGNUD_TEXTCOLOUR_CONTROL;
                szRetch++;
                *szRetch = NOEGNUD_TEXTCOLOUR_CODE_RGB;
                szRetch++;
                *szRetch = uar;
                szRetch++;
                *szRetch = uag;
                szRetch++;
                *szRetch = uab;
                szRetch++;
                *szRetch = 0;

                strcpy(szRetch, haystack);
                szRetch += strlen(haystack);
            };

            *szRetch = 0;
        }
    } else {
        return (char *) haystack;
    }
    return szReturn;
}

char *
noegnud_textcolour_rgb_text(const char *haystack, const char *needle,
                            float br, float bg, float bb, float ar, float ag,
                            float ab)
{
    struct re_pattern_buffer *pbuffer;
    char *regex_error;
    char *szReturn;

    re_syntax_options = RE_SYNTAX_EMACS;

    pbuffer = noegnud_mem_malloc(sizeof(struct re_pattern_buffer));

    pbuffer->translate = 0;
    pbuffer->fastmap = 0;
    pbuffer->buffer = 0;
    pbuffer->allocated = 0;

    if ((regex_error =
             (char *) re_compile_pattern(needle, strlen(needle), pbuffer))) {
        printf("[WARNING] noegnud_textcolour_rgb_text: failed regex "
               "compilation of \"%s\" : %s\n",
               needle, regex_error);
        szReturn = (char *) haystack;
    } else {
        szReturn = noegnud_textcolour_rgb_pbuffer(haystack, pbuffer, br, bg,
                                                  bb, ar, ag, ab);
    }

    noegnud_mem_free(pbuffer);
    return szReturn;
}

int
noegnud_textcolour_strlen(const char *str)
{
    char *ch;
    int count;

    count = 0;
    ch = (char *) str;
    while (*ch) {
        while (*ch == NOEGNUD_TEXTCOLOUR_CONTROL) {
            ch++;
            switch (*ch) {
            case NOEGNUD_TEXTCOLOUR_CODE_META:
                break;
            case NOEGNUD_TEXTCOLOUR_CODE_RGB:
                ch += 4;
                break;
            case NOEGNUD_TEXTCOLOUR_CODE_RGBA:
                ch += 5;
                break;
            case NOEGNUD_TEXTCOLOUR_CODE_FONT:
                ch += 5;
                break;
            case NOEGNUD_TEXTCOLOUR_CODE_UNDERLINE:
                ch += 2;
                break;
            case NOEGNUD_TEXTCOLOUR_CODE_BOLD:
                ch += 2;
                break;
            case NOEGNUD_TEXTCOLOUR_CODE_ITALICS:
                ch += 2;
                break;
            }
        }
        if (*ch)
            count++;
        ch++;
    }

    return count;
}
