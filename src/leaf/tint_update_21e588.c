// While in state 8 or 9, build the tint parameters for the current index (full scale when disabled or unset), pick the next state from the index and apply them.
// SLY3_CFLAGS: -Os -G0
struct Tint { float scale; int pad04, pad08; float level; float u, v; int pad18, pad1C; };
struct Entry { float u, v, w, x; };
struct Self {
    unsigned char opaque00[0x94];
    int state;
    unsigned char opaque98[0x130 - 0x98];
    int enabled;
    int index;
};
extern struct Entry D_00325FE0[];
extern int D_00326000[];
void *func_00292034(void *destination, int value, unsigned int count);
void func_00262848(struct Self *self, struct Tint *tint);

void func_0021E588(struct Self *self)
{
    struct Tint tint;
    if ((unsigned int)(self->state - 8) >= 2) return;
    if (self->enabled == 0 || self->index == -1) {
        func_00292034(&tint, 0, 0x20);
        tint.level = 1.0f;
        tint.scale = 1.0f;
    } else {
        struct Entry *entry;
        func_00292034(&tint, 0, 0x20);
        entry = &D_00325FE0[self->index];
        tint.scale = 0.75f;
        tint.u = entry->u;
        tint.v = entry->v;
        tint.level = 0.75f;
    }
    if (self->index == -1) self->state = 8;
    else self->state = D_00326000[self->index];
    func_00262848(self, &tint);
}
