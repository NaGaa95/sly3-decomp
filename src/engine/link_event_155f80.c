// SLY3_CFLAGS: -Os -G0
struct LinkRecord { unsigned char prefix[8]; int value; };
struct LinkPair { int id; int other; };
struct LinkObject { unsigned char prefix[0x190]; int id; };
struct LinkTarget { unsigned char prefix[0x13C]; struct LinkObject *object; };
struct LinkSelf { unsigned char prefix[0x18]; int word18; unsigned char gap1C[0x127C - 0x1C]; struct LinkTarget *target; };
struct LinkOther { unsigned char prefix[0x1A4]; void *entry; };
extern unsigned char D_0036C700[];
extern unsigned char D_00475480[];
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
struct LinkRecord *func_00185720(void *table, struct LinkSelf *self);
int *func_00185860(void *table, struct LinkSelf *self, struct LinkPair *pair);
void func_001857E8(void *table, struct LinkOther *other, int value);
int func_0014DBA0(void *entry);
int func_0025E150(void);
int func_0017E208(void *game, int a, int b, int c, int d, struct LinkObject **out);
void func_00155F80(struct LinkSelf *self, int kind, struct LinkOther *other)
{
    unsigned char frame[16];
    struct LinkPair pair;
    struct LinkObject *objects[32];
    func_001D2770(frame);
    switch(kind) {
    case 0: {
        struct LinkRecord *record = func_00185720(D_0036C700, self);
        if(other->entry) record->value = func_0014DBA0(other->entry);
        else record->value = -1;
        if(self->target) {
            if(!other->entry) {
                int *slot = func_00185860(D_0036C700, self, 0);
                if(slot) *slot = -1;
            }
            func_001857E8(D_0036C700, other, func_0014DBA0(self->target));
        } else func_001857E8(D_0036C700, other, self->word18);
        break;
    }
    case 1: {
        int *slot = func_00185860(D_0036C700, self, 0);
        if(slot) *slot = -1;
        func_00185720(D_0036C700, self)->value = -1;
        break;
    }
    case 2: {
        int *slot = func_00185860(D_0036C700, self, &pair);
        if(slot) *slot = func_0014DBA0(self->target);
        func_00185720(D_0036C700, self)->value = -1;
        if(slot) {
            if(pair.id == func_0025E150()) {
                int count = func_0017E208(D_00475480, 5, 0x23, 0, 0x20, objects);
                int i;
                for(i = 0; i < count; i++) {
                    if(objects[i]->id == pair.other) { self->target->object = objects[i]; break; }
                }
            }
        }
        break;
    }
    }
    func_001D2798(frame, 2);
}
