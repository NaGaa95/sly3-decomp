#ifndef SLY3_RUNTIME_SHUFFLE_PAIR_ACCESS_H
#define SLY3_RUNTIME_SHUFFLE_PAIR_ACCESS_H

/* The original values are two separately consumed32-bit fields. Four-byte
 * alignment is real: copies use unaligned64-bit load/store pairs. */
struct RuntimeShufflePair {
    int first;
    int second;
#ifdef __cplusplus
    bool operator==(const RuntimeShufflePair &other) const
    {
        return first == other.first && second == other.second;
    }
#endif
};

struct RuntimeShufflePairBag {
    void *vtable;
    int count;
    struct RuntimeShufflePair *items;
    int cursor;
    void *heap;
};

typedef char RuntimeShufflePairSize8[(sizeof(struct RuntimeShufflePair) == 8) ? 1 : -1];
typedef char RuntimeShufflePairAlignment4[(__alignof__(struct RuntimeShufflePair) == 4) ? 1 : -1];
typedef char RuntimeShufflePairBagSize20[(sizeof(struct RuntimeShufflePairBag) == 20) ? 1 : -1];
typedef char RuntimeShufflePairItemsAt8[((unsigned int)&(((struct RuntimeShufflePairBag *)0)->items) == 8) ? 1 : -1];
typedef char RuntimeShufflePairCursorAtC[((unsigned int)&(((struct RuntimeShufflePairBag *)0)->cursor) == 12) ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
void func_002BFED8(struct RuntimeShufflePairBag *array, int count,
                  const struct RuntimeShufflePair *items, void *heap);
struct RuntimeShufflePair func_002C0060(struct RuntimeShufflePairBag *array);
#ifdef __cplusplus
}
#endif
#endif
