#include <stdlib.h>
#include <stdio.h>

#include "math.h"
#include "string.h"

#include "noegnud_mem.h"
#include "noegnud_collection.h"

static void
default_destructor(void *p)
{
    noegnud_mem_free(p);
}

noegnud_tcollection *
noegnud_collection_create(const char *name, void *data,
                          void (*destructor)(void *))
{
    noegnud_tcollection *collection;
#ifdef NOEGNUDDEBUG
    char *debug_coll;
    char debug_coll_t;
#endif

#ifdef NOEGNUDDEBUG
    if (data == NULL) {
        printf("[FATAL:%s:%d] collection creation with a NULL data pointer! "
               "aborting ...\n",
               __FILE__, __LINE__);
        exit(-1);
    }
#endif

    collection = noegnud_mem_malloc(sizeof(noegnud_tcollection));
    collection->name = noegnud_mem_malloc(strlen(name) + 1);
    strcpy(collection->name, name);
    collection->data = data;
    collection->destructor = destructor ? destructor : default_destructor;
#ifdef NOEGNUDDEBUG
    //	printf("[DEBUG] testing new collection data integrity for [\"%s\"]
    //...\n",name);
    debug_coll = data;
    debug_coll_t = *debug_coll;
#endif
    collection->next = NULL;

    return collection;
}
noegnud_tcollection *
noegnud_collection_add(noegnud_tcollection *collection, const char *name,
                       void *data, void (*destructor)(void *))
{
    noegnud_tcollection *add;
    noegnud_tcollection *made;

    add = collection;
    if (!add)
        return noegnud_collection_create(name, data, destructor);
    while (add->next) {
        if (!strcmp(name, add->name)) {
#ifdef NOEGNUDDEBUG
//			printf("[DEBUG] reassigning data for collection value
//[\"%s\"]\n",name);
#endif

            // ***** FAILED TO FIND REFERENCE ..... well, duh, it might be
            // part of "ram debug" collection ...

            add->destructor(add->data);
            add->destructor = destructor ? destructor : default_destructor;
            add->data = data;
            return add;
        }
        add = add->next;
    }
    made = add->next = noegnud_collection_create(name, data, destructor);
    return made;
}
void
noegnud_collection_destroy(noegnud_tcollection **collectionp)
{
    noegnud_tcollection *p;

    p = *collectionp;
    while (p != NULL) {
        noegnud_tcollection *q;
        q = p;
        p = q->next;
        q->destructor(q->data);
        noegnud_mem_free(q->name);
        noegnud_mem_free(q);
    }
    *collectionp = NULL;
}

noegnud_tcollection *
noegnud_collection_structure(noegnud_tcollection *collection,
                             const char *name)
{
    noegnud_tcollection *get;
    get = collection;
    while (get) {
        if (!strcmp(name, get->name)) {
            return get;
        }
        get = get->next;
    }
    return NULL;
}

void *
noegnud_collection_data(noegnud_tcollection *collection, const char *name)
{
    noegnud_tcollection *get;

    get = noegnud_collection_structure(collection, name);
    if (get)
        return get->data;
    return NULL;
}
