// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Init {
    unsigned char pad0[0x1B8];
    int mode;
    unsigned char pad1BC[0x234 - 0x1BC];
    void *spawn;
    void *channel;
    unsigned char pad23C[0x258 - 0x23C];
    void *cache;
    unsigned char pad25C[0x410 - 0x25C];
    void *notifier;
    void *notifierOut;
    unsigned char pad418[0x434 - 0x418];
    void *anim;
    unsigned char pad438[0x43C - 0x438];
    float animA, animB;
    void *controller;
    unsigned char pad448[0x4F0 - 0x448];
    void *shuffled;
    unsigned char pad4F4[0x55C - 0x4F4];
    int resourceId;
    void *resource;
};
extern char D_00348B98[];
extern char D_0036B118[];
extern qword D_00317560;
void func_001F3BF8(struct Init *self);
void func_001C8970(struct Init *self, int a, void *table, int b);
void func_002181D0(struct Init *self);
void func_0023AAE8(void *object, struct Init *self, int id, int n, void **output);
void func_00273E48(void *controller, void *first, void *second, int mode);
void *func_0023DDA0(struct Init *self, int identity, int kind);
void *func_00130078(struct Init *self, void *owner, int a, int b, int c, qword q);
float func_001368E0(void *anim, int id);
void *func_00231138(int uid, int count);
void func_001F4670(struct Init *self, int n);
int func_001D27F0(int bytes);
void *func_002BC1C8(int storage, int count, const int *identifiers, void *heap);
void *func_0023F3B8(struct Init *self, int identifier);
// Construct the object: base setup, notifier/controller hookups, spawned channel, animation timings, asset cache and the shuffled sound list.
void func_00213C90(struct Init *self)
{
    void *found;
    func_001F3BF8(self);
    func_001C8970(self, 2, D_00348B98, 0);
    func_002181D0(self);
    if (self->notifier)
        func_0023AAE8(self->notifier, self, -1, 0, &self->notifierOut);
    if (self->controller && self->mode != 2)
        func_00273E48(self->controller, 0, 0, 0);
    self->spawn = func_0023DDA0(self, 0x78F, 6);
    if (self->spawn)
        self->channel = func_00130078(self, self->spawn, 1, 8, 2, D_00317560);
    if (self->anim) {
        self->animA = func_001368E0(self->anim, 0x42);
        self->animB = func_001368E0(self->anim, 0x43);
    }
    self->cache = func_00231138(0x320, 0x10);
    if (self->mode != 2) {
        func_001F4670(self, 1);
        {
            int ids[5] = { 0x3E, 0x3F, 0x40, 0x41, 0x42 };
            self->shuffled = func_002BC1C8(func_001D27F0(0x14), 5, ids, D_0036B118);
        }
    }
    found = func_0023F3B8(self, self->resourceId);
    self->resource = found;
    if (found)
        *(unsigned long *)((char *)found + 0x18) |= 0x10000;
}
