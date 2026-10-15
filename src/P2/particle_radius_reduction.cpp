// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions

typedef int QWORD __attribute__((mode(TI)));
struct ReductionEntry {
    short delta, reserved;
    union {
        void *(*matrix)(void *);
        int (*count)(void *, QWORD, float);
    };
};
struct ReductionChild {
    char prefix[0x24];
    ReductionChild *next;
    char reserved28[0x18];
    ReductionEntry *operations;
};
struct CachedOwner { char prefix[0x6C]; ReductionChild *head; };
struct LOOKUP_ROW { int target_key, owner_key; void *result; };
struct ReductionState {
    char prefix[0xC];
    ReductionEntry *table;
    char reserved10[0xC8];
    int count;
    char reservedDC[0x30];
    float radius;
    int minimum, maximum;
};
extern "C" {
void *func_001FE9B8(void *settings);
void func_001FECC0(void *state, int value);
void func_002BE948(void *object, int flags);
}

extern "C" void func_001FEB90(void *object)
{
    ReductionState *state = (ReductionState *)object;
    unsigned int total = 0;
    for (int i = 0; i < state->count; ++i) {
        LOOKUP_ROW *rows = (LOOKUP_ROW *)((char *)object + 0xDC);
        void *settings = rows[i].result;
        if (settings) {
            CachedOwner *owner = (CachedOwner *)func_001FE9B8(settings);
            if (owner) {
                QWORD addressOnlyTemporary;
                for (ReductionChild *child = owner->head; child; child = child->next) {
                    ReductionEntry *entry = &child->operations[6];
                    void *receiver = (char *)child + entry->delta;
                    ReductionEntry *matrixEntry = &state->table[36];
                    const QWORD *matrix = (const QWORD *)matrixEntry->matrix(
                        (char *)object + matrixEntry->delta);
                    total += entry->count(receiver, matrix[3], state->radius);
                }
                func_002BE948(&addressOnlyTemporary, 2);
            }
        }
    }
    if ((int)total >= state->minimum)
        func_001FECC0(object, 0);
    else if (state->maximum >= (int)total)
        func_001FECC0(object, 1);
}
