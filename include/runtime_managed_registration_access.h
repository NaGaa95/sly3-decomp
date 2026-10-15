#ifndef SLY3_RUNTIME_MANAGED_REGISTRATION_ACCESS_H
#define SLY3_RUNTIME_MANAGED_REGISTRATION_ACCESS_H

// Observed first8-byte link encoding; pool element size remains separate.
typedef struct RuntimeManagedLinkedCell {
    int references;
    unsigned int previousGroup : 4;
    unsigned int previousIndex : 11;
    unsigned int retainedBit15 : 1;
    unsigned int nextGroup : 4;
    unsigned int nextIndex : 11;
    unsigned int generation : 1;
} RuntimeManagedLinkedCell;
typedef struct RuntimeManagedListHead { RuntimeManagedLinkedCell *first; } RuntimeManagedListHead;
typedef char RuntimeManagedLinkSize8[sizeof(RuntimeManagedLinkedCell) == 8 ? 1 : -1];

// The decoder writes a whole32-bit output object; this caller reads its low16 view.
// The measured target is little-endian. No undersized output storage is passed.
typedef union RuntimeManagedDecoderWord {
    unsigned int whole;
    unsigned short low16;
} RuntimeManagedDecoderWord;
typedef char RuntimeManagedDecoderSize4[sizeof(RuntimeManagedDecoderWord) == 4 ? 1 : -1];

struct S;
void func_002B4098(struct S *cell, unsigned int *group, unsigned int *index);
void func_002B4458(struct S *cell, unsigned int *group, unsigned int *index);
void func_002B4818(struct S *cell, unsigned int *group, unsigned int *index);
void func_002B4BD8(struct S *cell, unsigned int *group, unsigned int *index);
void func_002B41C8(struct S *cell, void *table);
void func_002B4588(struct S *cell, void *table);
void func_002B4948(struct S *cell, void *table);
void func_002B4D08(struct S *cell, void *table);

#endif
