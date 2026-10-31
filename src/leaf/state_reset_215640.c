// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VirtualEntry { short adjustment; short reserved; void (*call)(void *); };
struct Hook { unsigned char pad0[0xC]; struct VirtualEntry *vtable; };
struct Slot { unsigned char data[0x1C]; };
struct ResetSelf {
    unsigned char pad0[0x190];
    int curA, curB;
    int srcA, srcB;
    int saveA, saveB;
    unsigned char pad1A8[0x1B8 - 0x1A8];
    int mode;
    unsigned char pad1BC[0x260 - 0x1BC];
    int selected;
    unsigned char pad264[4];
    int flag268;
    unsigned char pad26C[4];
    struct Slot slots[2][6];
    int counts[2];
    unsigned char pad3C8[0x414 - 0x3C8];
    void *listener;
    unsigned char pad418[0x434 - 0x418];
    void *target;
    unsigned char block438[0x44C - 0x438];
    struct Hook *hook;
    unsigned char pad450[0x550 - 0x450];
    int busy;
};
extern float D_00325BBC;
void func_00239FE0(void *listener, int code);
void func_00217D50(struct ResetSelf *self, struct Slot *slot, int zero, float value);
void func_00137588(void *target, struct ResetSelf *self, int one, void *block, float a, float b);
void func_00215FD0(struct ResetSelf *self, int arg);
void func_002159D8(struct ResetSelf *self, int arg);
void func_002171E8(struct ResetSelf *self, int arg);
void func_00215388(struct ResetSelf *self, int arg);
// Reset the object: restore the saved counters, reinitialize every slot, clear the transient state and pick the starting selection.
void func_00215640(struct ResetSelf *self)
{
    int i, j;
    int first = self->srcA, second = self->srcB;
    self->curA = first;
    self->curB = second;
    self->saveA = first;
    self->saveB = second;
    if (self->listener)
        func_00239FE0(self->listener, 0x92);
    for (i = 0; i < 2; i++) {
        int count = self->counts[i];
        for (j = 0; j < count; j++)
            func_00217D50(self, &self->slots[i][j], 0, D_00325BBC);
    }
    func_00137588(self->target, self, 1, self->block438, 0.0f, 0.0f);
    if (self->hook)
        self->hook->vtable[9].call((char *)self->hook + self->hook->vtable[9].adjustment);
    func_00215FD0(self, 0);
    func_002159D8(self, 0);
    if (self->mode == 2) {
        if (self->flag268)
            func_002171E8(self, 1);
        else
            func_002171E8(self, 2);
    } else {
        func_002171E8(self, -1);
    }
    self->busy = 0;
    self->selected = -1;
    func_00215388(self, -1);
}
