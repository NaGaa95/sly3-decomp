#ifndef PRIVATE_SELECTION_ACCESS_TYPES_H
#define PRIVATE_SELECTION_ACCESS_TYPES_H

/* Shared views of the original fields used by the three selection methods.
   These prefixes do not declare an allocation size or a unique dynamic class. */
typedef struct SelectionVirtualEntry {
    short adjustment;
    short reserved;
    void *function;
} SelectionVirtualEntry;

typedef struct SelectionResource {
    char reserved0[0xC];
    SelectionVirtualEntry *vtable;
    char reserved10[0x48 - 0x10];
    int state48;
    char reserved4C[0x60 - 0x4C];
    int value60;
    int value64;
    int value68;
} SelectionResource;

typedef struct SelectionEntry {
    int id;
    int auxiliary;
} SelectionEntry;

typedef struct Selection {
    char reserved0[0xC];
    SelectionVirtualEntry *vtable;
    char reserved10[0x34 - 0x10];
    SelectionResource *child;
    char reserved38[0x50 - 0x38];
    int state;
    float changed_at;
    unsigned int count;
    SelectionEntry entries[67];
    int index;
    int first;
    int selected;
    int value280;
    int value284;
    int value288;
} Selection;

typedef char SelectionEntryWidth[(sizeof(SelectionEntry) == 8) ? 1 : -1];
typedef char SelectionVirtualEntryWidth[(sizeof(SelectionVirtualEntry) == 8) ? 1 : -1];
typedef char SelectionCountWidth[(sizeof(unsigned int) == 4) ? 1 : -1];
typedef char SelectionAccessViewWidth[(sizeof(Selection) == 0x28C) ? 1 : -1];

#endif
