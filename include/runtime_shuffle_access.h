#ifndef SLY3_RUNTIME_SHUFFLE_ACCESS_H
#define SLY3_RUNTIME_SHUFFLE_ACCESS_H

// Actual20-byte storage shared by the three original scalar shuffle specializations.
struct SHUFFLED_IDENTIFIERS {
    void *vtable;
    int count;
    int *items;
    int cursor;
    void *heap;
};
typedef char RuntimeShuffleSizeCheck[sizeof(struct SHUFFLED_IDENTIFIERS) == 20 ? 1 : -1];
typedef char RuntimeShuffleHeapOffsetCheck[((unsigned int)&(((struct SHUFFLED_IDENTIFIERS *)0)->heap)) == 0x10 ? 1 : -1];

// The admitted receiver-only base constructors use this opaque access view.
struct S;
struct S *func_002BC090(struct S *object);
struct S *func_002BF768(struct S *object);
struct S *func_002BF910(struct S *object);

void func_002BC0A8(struct SHUFFLED_IDENTIFIERS *object, int count, const int *items, void *heap);
void func_002BF780(struct SHUFFLED_IDENTIFIERS *object, int count, const int *items, void *heap);
void func_002BF928(struct SHUFFLED_IDENTIFIERS *object, int count, const int *items, void *heap);

struct SHUFFLED_IDENTIFIERS *func_002BC1C8(void *storage, int count, const int *identifiers, void *heap);
struct SHUFFLED_IDENTIFIERS *func_002BF8A0(void *storage, int count, const int *identifiers, void *heap);
struct SHUFFLED_IDENTIFIERS *func_002BFA48(void *storage, int count, const int *identifiers, void *heap);

#endif
