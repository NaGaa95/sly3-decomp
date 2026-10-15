#ifndef SLY3_RUNTIME_MANAGED_REMOVAL_ACCESS_H
#define SLY3_RUNTIME_MANAGED_REMOVAL_ACCESS_H
#include "runtime_managed_registration_access.h"

// One coherent initialized word plus its actual little-endian read views.
typedef union RuntimeManagedRemovalWord {
    unsigned int whole;
    struct { unsigned short low16, high16; } halves;
    struct {
        unsigned int previousGroup : 4;
        unsigned int previousIndex : 11;
        unsigned int retainedBit15 : 1;
        unsigned int nextGroup : 4;
        unsigned int nextIndex : 11;
        unsigned int generation : 1;
    } fields;
} RuntimeManagedRemovalWord;
typedef char RuntimeManagedRemovalWordSize4[sizeof(RuntimeManagedRemovalWord) == 4 ? 1 : -1];

typedef struct RuntimeManagedRemovalCell12 {
    unsigned int opaque00;
    RuntimeManagedRemovalWord links;
    unsigned char opaque08[4];
} RuntimeManagedRemovalCell12;
typedef struct RuntimeManagedRemovalCell16 {
    unsigned char opaque00[8];
    RuntimeManagedRemovalWord links;
    unsigned char opaque0c[4];
} RuntimeManagedRemovalCell16;
typedef struct RuntimeManagedRemovalCell24 {
    unsigned int opaque00;
    RuntimeManagedRemovalWord links;
    unsigned char opaque08[16];
} RuntimeManagedRemovalCell24;
typedef struct RuntimeManagedRemovalCell28 {
    unsigned int opaque00;
    RuntimeManagedRemovalWord links;
    unsigned char opaque08[20];
} RuntimeManagedRemovalCell28;
typedef char RuntimeManagedRemovalSize12[sizeof(RuntimeManagedRemovalCell12) == 12 ? 1 : -1];
typedef char RuntimeManagedRemovalSize16[sizeof(RuntimeManagedRemovalCell16) == 16 ? 1 : -1];
typedef char RuntimeManagedRemovalSize24[sizeof(RuntimeManagedRemovalCell24) == 24 ? 1 : -1];
typedef char RuntimeManagedRemovalSize28[sizeof(RuntimeManagedRemovalCell28) == 28 ? 1 : -1];
typedef char RuntimeManagedRemovalOffset4[((unsigned int)&(((RuntimeManagedRemovalCell12 *)0)->links)) == 4 ? 1 : -1];
typedef char RuntimeManagedRemovalOffset8[((unsigned int)&(((RuntimeManagedRemovalCell16 *)0)->links)) == 8 ? 1 : -1];

void func_002B3B90(struct S *cell);
void func_002B3F48(struct S *cell);
void func_002B4308(struct S *cell);
void func_002B46C8(struct S *cell);
void func_002B4A88(struct S *cell);
void func_002B4E48(struct S *cell);

#endif
