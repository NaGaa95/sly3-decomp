// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Clock { float t; };
extern struct Clock g_clock;
extern unsigned char D_0036C700[];
struct Triple { int a, b, c; int pad; };
struct Self {
    unsigned char pad0[0x1F0]; int state; float stateTime;
    unsigned char pad1F8[0x240 - 0x1F8]; struct Triple last; struct Triple entries[6];
};
int func_001F43F0(void);
void func_001F43D0(struct Self *self, int value);
void func_00240DB0(struct Self *self);
void func_001854C8(void *list, int kind, struct Self *self);
void func_0019BA10(struct Self *self, struct Triple *entry);
static inline void ClearTriple(struct Triple *t) { t->c = 0; t->b = 0; t->a = 0; }
void func_0019DC10(struct Self *self, int state)
{
    int old = self->state;
    if (old == state) return;
    switch (old) {
    case -1:
        func_001F43D0(self, func_001F43F0());
        break;
    case 4: case 5:
        func_00240DB0(self);
        break;
    }
    self->state = state;
    self->stateTime = g_clock.t;
    switch (state) {
    case 5:
        func_001854C8(D_0036C700, 0x10, self);
    case 0: case 1: case 2: case 4:
        ClearTriple(&self->last);
        break;
    case 3:
        break;
    }
    func_0019BA10(self, state == -1 ? 0 : &self->entries[state]);
}
/* Next .rodata item of the original unit (a float literal read by func_0019DDC8); it follows the jump table. */
const float D_00322058 = 25.0f;
