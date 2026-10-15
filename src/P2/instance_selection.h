#ifndef SLY3_P2_INSTANCE_SELECTION_H
#define SLY3_P2_INSTANCE_SELECTION_H
#include "scene.h"

// Borrowed views of the instance tables and their 80-byte state entries.
struct INSTANCE_SELECTION_ENTRY {
    SCENE_OBJECT *owner;
    INSTANCE_SELECTION_ENTRY *next;
    int active;
    int reservedC;
    float matrix[16];
};
struct INSTANCE_SELECTION_TABLE {
    int object_count;
    SCENE_OBJECT **objects;
    int capacity;
    int first;
    char reserved10[0x68 - 0x10];
    INSTANCE_SELECTION_ENTRY *entries;
};
struct INSTANCE_SELECTION_OWNER {
    char reserved[0xD0];
    INSTANCE_SELECTION_TABLE *table;
    int mode;
    INSTANCE_SELECTION_ENTRY *head;
};
extern "C" {
    int func_001FB5D8(INSTANCE_SELECTION_OWNER *, INSTANCE_SELECTION_ENTRY *);
    INSTANCE_SELECTION_ENTRY *func_001FB600(INSTANCE_SELECTION_OWNER *, int index);
    int func_001C8610(SCENE_OBJECT *);
    int func_001FB620(INSTANCE_SELECTION_OWNER *, INSTANCE_SELECTION_ENTRY *);
    INSTANCE_SELECTION_ENTRY *func_001FBA28(INSTANCE_SELECTION_OWNER *, int minimum);
}
#define INSTANCE_OFF(t,m) ((unsigned int)&((t *)0)->m)
typedef char instance_selection_layout[
    (sizeof(void *) == 4 && sizeof(INSTANCE_SELECTION_ENTRY) == 0x50 &&
     sizeof(INSTANCE_SELECTION_TABLE) == 0x6C &&
     INSTANCE_OFF(INSTANCE_SELECTION_ENTRY, active) == 8 &&
     INSTANCE_OFF(INSTANCE_SELECTION_ENTRY, matrix) == 0x10 &&
     INSTANCE_OFF(INSTANCE_SELECTION_TABLE, first) == 0xC &&
     INSTANCE_OFF(INSTANCE_SELECTION_TABLE, entries) == 0x68 &&
     INSTANCE_OFF(INSTANCE_SELECTION_OWNER, table) == 0xD0 &&
     INSTANCE_OFF(INSTANCE_SELECTION_OWNER, mode) == 0xD4 &&
     INSTANCE_OFF(INSTANCE_SELECTION_OWNER, head) == 0xD8) ? 1 : -1];
#undef INSTANCE_OFF
#endif
