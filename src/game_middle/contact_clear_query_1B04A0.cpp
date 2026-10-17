// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/vector_intrinsics.h"

struct ClearMethod { short adjustment, word2; void *function; };
struct ClearTable {
    unsigned char prefix[0x120];
    ClearMethod matrix;
    unsigned char gap128[0x210 - 0x128];
    ClearMethod blocked;
};
struct ClearObject { unsigned char prefix[0xC]; ClearTable *methods; };
struct ClearPart {
    unsigned char prefix[8];
    void *owner;
    ClearObject *object;
    unsigned char rest[0x30];
};
union ClearVector { qword packed; float lane[4]; };
struct ClearEntry {
    ClearPart part[2];
    ClearVector vector;
    unsigned char gap90[0x9C - 0x90];
    int kind;
    unsigned char gapA0[0xAC - 0xA0];
    ClearEntry *next;
};
struct ClearNode { ClearEntry *first; ClearNode *next; };
struct ClearOwner { unsigned char prefix[0x64]; ClearNode *nodes; };
struct ClearSelf {
    unsigned char prefix0[0xC];
    ClearTable *methods;
    unsigned char gap10[0xDC - 0x10];
    ClearOwner *owner;
};
struct ClearMatrix { qword position; };
extern "C" {
extern float D_00322B30[3];
extern float D_00322B40[2];
extern char D_0036BD20[];
qword func_00120D98(qword first, qword second);
float func_00171C98(void *receiver);

static inline float Clamp(float x, float lower, float upper)
{
    if (x < lower) return lower;
    if (x > upper) return upper;
    return x;
}

int func_001B04A0(ClearSelf *self)
{
    ClearNode *node;
    for (node = self->owner->nodes; node; node = node->next) {
        ClearEntry *entry;
        for (entry = node->first; entry; entry = entry->next) {
            float distance, scale, limit;
            ClearMethod *method;
            int side;
            ClearPart *other;
            if (entry->kind == 10 || entry->kind == 14)
                continue;
            if (0.7f < __builtin_fabsf(entry->vector.lane[2]))
                continue;
            method = &self->methods->matrix;
            distance = PackedVectorX(func_00120D98(
                ((ClearMatrix *(*)(void *))method->function)((char *)self + method->adjustment)->position,
                entry->vector.packed));
            scale = func_00171C98(D_0036BD20);
            limit = D_00322B30[0] + scale * (D_00322B30[1] + scale * D_00322B30[2]);
            limit = Clamp(limit, D_00322B40[0], D_00322B40[1]);
            if (limit < distance)
                continue;
            side = entry->part[1].owner != self;
            other = &entry->part[side];
            method = &other->object->methods->blocked;
            if (((int (*)(void *))method->function)((char *)other->object + method->adjustment))
                return 1;
        }
    }
    return 0;
}
}
