#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "noegnud_collection.h"
#include "noegnud_typeloader.h"
#include "noegnud_extern.h"
#include "noegnud_mem.h"
#include "noegnud_common.h"
#include "noegnud_config.h"

#include "noegnud_lang.h"

static noegnud_tcollection *noegnud_lang = NULL;
static void noegnud_lang_done(void);
static void noegnud_lang_load(char *filename);

void
noegnud_lang_init(void)
{
    atexit(noegnud_lang_done);
    noegnud_lang_load(noegnud_options_language->value);
}

void
noegnud_lang_done(void)
{
    noegnud_collection_destroy(&noegnud_lang);
}

static void
noegnud_lang_load_parser(char *setting, int nparams, char *params, void *data)
{
    char *value;

    if (!strcmp(setting, "$include$")) {
        noegnud_lang_load(params);
        return;
    }

    if ((value = noegnud_collection_data(noegnud_lang, setting))) {
        // realloc(value,strlen(params)+1);
        strcpy(value, params);
    } else {
        // value=noegnud_mem_malloc(strlen(params)+1);
        value = noegnud_mem_malloc(256);
        strcpy(value, params);
        if (noegnud_lang) {
            noegnud_collection_add(noegnud_lang, setting, value, NULL);
        } else {
            noegnud_lang = noegnud_collection_create(setting, value, NULL);
        }
    }
}

static void
noegnud_lang_load(char *langname)
{
    char filename[2048];
    char *szHomedir;

    noegnud_typeloader_IFS = 0;
    szHomedir = noegnud_options_get_home();
    sprintf(filename, "%s/lang/%s.lang", szHomedir, langname);
    noegnud_mem_free(szHomedir);
    if (!noegnud_common_file_exists(filename))
        sprintf(filename, "../" NOEGNUD_DATADIR "/lang/%s.lang", langname);
    printf("* loading language : %s (%s)\n", langname, filename);
    noegnud_typeloader_parsefile(noegnud_lang_load_parser, filename, 0);
}

char *
noegnud_lang_translate(const char *string)
{
    char *result;
    char *translation;
    char *replaced;

    noegnud_tcollection *walk_through;

    replaced =
        noegnud_common_str_replace(string, plname, NOEGNUD_LANG_PLNAME);

    if (!(result = noegnud_collection_data(noegnud_lang, replaced))) {
#ifdef NOEGNUDDEBUG
        int translated = 0;
#endif
        result = replaced;

        walk_through = noegnud_lang;
        while (walk_through) {
            replaced = noegnud_common_str_replace(
                result, walk_through->name, (char *) walk_through->data);
            if (replaced != result) {
                if (result != string)
                    noegnud_mem_free(result);
                result = replaced;
#ifdef NOEGNUDDEBUG
                translated = 1;
#endif
            }
            walk_through = walk_through->next;
        }
#ifdef NOEGNUDDEBUG
        if (!translated)
            printf("[UNTRANSLATED]: \"%s=?\"\n", replaced);
#endif
    }

    translation = noegnud_mem_malloc(strlen(result) + 1);
    strcpy(translation, result);

    if (replaced != string)
        noegnud_mem_free(replaced);

    replaced =
        noegnud_common_str_replace(translation, NOEGNUD_LANG_PLNAME, plname);
    if (replaced != translation)
        noegnud_mem_free(translation);
    return replaced;
}
