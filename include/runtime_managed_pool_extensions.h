#ifndef SLY3_RUNTIME_MANAGED_POOL_EXTENSIONS_H
#define SLY3_RUNTIME_MANAGED_POOL_EXTENSIONS_H
#include "runtime_managed_registration_access.h"

// This specialization's packed word is genuinely at+8, distinct from the +4 view.
typedef struct RuntimeManagedWideLinkedCell {
    unsigned char opaque00[8];
    unsigned int previousGroup : 4;
    unsigned int previousIndex : 11;
    unsigned int retainedBit15 : 1;
    unsigned int nextGroup : 4;
    unsigned int nextIndex : 11;
    unsigned int generation : 1;
} RuntimeManagedWideLinkedCell;
typedef struct RuntimeManagedWideListHead { RuntimeManagedWideLinkedCell *first; } RuntimeManagedWideListHead;
typedef char RuntimeManagedWideLinkSize12[sizeof(RuntimeManagedWideLinkedCell) == 12 ? 1 : -1];

void func_002B3930(struct S *cell, unsigned int *group, unsigned int *index);
void func_002B3CD8(struct S *cell, unsigned int *group, unsigned int *index);
void func_002B3A48(struct S *cell, void *table);
void func_002B3E08(struct S *cell, void *table);

#endif
