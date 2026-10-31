// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ActionEntry { int state; int button; int target; };
struct ActionSelf {
    unsigned char prefix0[0x130];
    int arg130;
    void *input;
    unsigned char gap138[0x190 - 0x138];
    int mode;
    unsigned char gap194[4];
    void *machine;
    int count;
    struct ActionEntry entries[8];
    unsigned char gap200[0x24C - 0x200];
    int pending;
};
extern char D_00475480[];
extern char D_0046F810[];
void func_0023C660(struct ActionSelf *self);
int func_001A99E0(void *pending);
int func_00239E70(void *machine);
int func_001A7A80(void *input, int button, float t);
void *func_0017E1B8(void *world, int kind, int id, void *owner);
void func_00225EE8(void *object, int arg);
void func_0021DDC0(void *object, int arg);
void func_00220590(void *object, int arg);
void func_00213728(struct ActionSelf *self, int index);
// While the controller is in mode 1: handle a pending request, otherwise fire the first action entry whose state matches the machine and whose button is down.
void func_00213250(struct ActionSelf *self)
{
    int i, pendingIndex;
    func_0023C660(self);
    if (self->mode == 0)
        return;
    if (self->mode != 1)
        return;
    if (!self->machine)
        return;
    pendingIndex = func_001A99E0(&self->pending);
    if (!pendingIndex) {
        for (i = 0; i < self->count; i++) {
            struct ActionEntry *entry = &self->entries[i];
            if (entry->state == func_00239E70(self->machine) && func_001A7A80(self->input, entry->button, 0.0f)) {
                void *object;
                if (entry->target == -1)
                    continue;
                if (entry->target == 0x429) {
                    func_0021DDC0(D_0046F810, self->arg130);
                    func_00220590(D_0046F810, 0);
                    return;
                }
                object = func_0017E1B8(D_00475480, 4, entry->target, self);
                if (object) {
                    func_00225EE8(object, 0);
                    return;
                }
            }
        }
    } else {
        func_00213728(self, pendingIndex);
    }
}
