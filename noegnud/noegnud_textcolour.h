#ifndef _NOEGNUD_TEXTCOLOUR_H_

#include <regex.h>

#define NOEGNUD_TEXTCOLOUR_CONTROL 0x01

#define NOEGNUD_TEXTCOLOUR_CODE_META NOEGNUD_TEXTCOLOUR_CONTROL
#define NOEGNUD_TEXTCOLOUR_CODE_RGB 0x02
#define NOEGNUD_TEXTCOLOUR_CODE_RGBA 0x03
#define NOEGNUD_TEXTCOLOUR_CODE_FONT 0x04
#define NOEGNUD_TEXTCOLOUR_CODE_UNDERLINE 0X05
#define NOEGNUD_TEXTCOLOUR_CODE_BOLD 0X06
#define NOEGNUD_TEXTCOLOUR_CODE_ITALICS 0X07

char *noegnud_textcolour_rgb_pbuffer(const char *haystack,
                                     struct re_pattern_buffer *needle,
                                     float br, float bg, float bb, float ar,
                                     float ag, float ab);
char *noegnud_textcolour_rgb_text(const char *haystack, const char *needle,
                                  float br, float bg, float bb, float ar,
                                  float ag, float ab);

int noegnud_textcolour_strlen(const char *str);

#endif
