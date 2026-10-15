// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Intrusive list membership uses the next link and recorded tail.
#include "m2c_prelude.h"
typedef struct DL { void *first; void *last; int link_offset; } DL;
typedef struct DLE { void *next; void *previous; } DLE;
s32 func_0011B0C0(DL *list, void *node) {
 DLE *link = (DLE *)((char *)node + list->link_offset);
 s32 found = 0;
 if (link->next != NULL || list->last == node) found = 1;
 return found;
}
