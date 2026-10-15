// Complete original function, inputs and emitted data independently reviewed.
// Switch descriptor arrays and choose the smallest eligible coordinate sum.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry {
    short delta, word2;
    union {
        void (*receiver)(void *);
        void (*identifier)(void *, int);
    }
    call;
};
struct Control {
    char pad0[0xC];
    struct VirtualEntry *table;
};
#include "selection_state_data.h"
struct SelectionState {
    char pad0[0xC];
    struct VirtualEntry *table;
    char pad10[0x30 - 0x10];
    int resourceId;
    struct Control *control;
    char pad38[0x50 - 0x38];
    int state;
    float transitionTime;
    int word58;
    int count;
    struct SelectionEntry *entries;
};
struct Clock {
    float words[16];
    float current;
};
extern struct Clock D_0036BB98;
extern char D_00475480[];
extern float D_003260A4;
void func_00165548(struct Clock *clock, int mode, float scale);
void func_001A93C8(void *game, int index, unsigned int flags);
void func_001A9420(void *game, int index, unsigned int flags);
void func_0021F948(struct SelectionState *state, int identifier);
void func_0021ED28(struct SelectionState *state, int mode, int parameter);
void func_0021F5F8(struct SelectionState *state);
void *func_0017E1B8(void *game, int flags, int keyWord, void *owner);
int func_00260D10(void);
void func_0021FAE0(struct SelectionState *state, int selection);
void func_0021FAE0(struct SelectionState *p, int selection) {
    if (selection == p->state) return;
    if (p->state == -1) {
        func_00165548(&D_0036BB98, 0, 0.0f);
        func_001A93C8(D_00475480, -1, 0);
    }
    func_0021F948(p, -1);
    p->state = selection;
    p->transitionTime = D_0036BB98.current;
    switch (selection) {
        case -1: {
            int i;
            if (p->control) {
                struct Control *control = p->control;
                control->table[54].call.receiver( (char *)control + control->table[54].delta);
            }
            for (i = 0; i < p->count; ++i) p->entries[i].selected = -1;
            p->count = 0;
            p->entries = 0;
            func_00165548(&D_0036BB98, 0, 1.0f);
            func_001A9420(D_00475480, -1, 0);
            p->table[11].call.receiver((char *)p + p->table[11].delta);
            func_0021ED28(p, -1, -1);
            p->control = 0;
            p->resourceId = -1;
            break;
        }
        case 0: p->resourceId = 0x426;
        p->count = 15;
        p->entries = D_00348BE0;
        break;
        case 1: p->resourceId = 0x427;
        p->count = 11;
        p->entries = D_00348DC0;
        break;
        case 2: p->resourceId = 0x428;
        p->count = 8;
        p->entries = D_00348F20;
        break;
    }
    if (p->state != -1) {
        func_0021F5F8(p);
        p->control = func_0017E1B8(D_00475480, 5, p->resourceId, 0);
        if (p->control) {
            if (!func_00260D10()) p->control = 0;
        }
        if (!p->control) {
            func_0021FAE0(p, -1);
        }
        else {
            float best;
            int identifier;
            int i;
            struct Control *control = p->control;
            control->table[53].call.identifier( (char *)control + control->table[53].delta, 0x37F);
            best = D_003260A4;
            identifier = -1;
            for (i = 0; i < p->count; ++i) {
                struct SelectionEntry *entry = &p->entries[i];
                if (entry->flags & 4) {
                    float positionSum = entry->x + entry->y;
                    if (positionSum < best) {
                        identifier = entry->identifier;
                        best = positionSum;
                    }
                }
            }
            func_0021F948(p, identifier);
        }
    }
}
typedef char virtual_entry_is_8[sizeof(struct VirtualEntry) == 8 ? 1 : -1];
