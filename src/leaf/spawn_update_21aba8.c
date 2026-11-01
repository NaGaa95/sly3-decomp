// Periodic spawner update: while the player object is in spawn state, pick a free or oldest record every second, create a candidate and spawn it, then schedule the next spawn (5 seconds when the player is not ready).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef unsigned int Quadword __attribute__((mode(TI)));
struct Template { unsigned char pad0[8]; int claimed; };
struct Placement { Quadword position; unsigned char orientation[0x30]; int enabled; };
struct Record { void *handle; float time; struct Template *source; };
struct Object { unsigned char pad[0x1B0]; int kind; };
struct Spawner {
    unsigned char pad00[0x48];
    int active;
    unsigned char pad4C[0x5C - 0x4C];
    float interval;
    float nextTime;
    unsigned char pad64[0x4C];
};
extern unsigned char D_00475480[];
struct Clock { float now, step; };
extern struct Clock D_0036BB98;
struct Object *func_001F4AD0(void *game, int a);
void func_001C8168(struct Spawner *self);
void func_0021ADF8(struct Spawner *self);
int func_0013B500(void *object, int id);
struct Record *func_0021AEB0(struct Spawner *self);
struct Template *func_0021AF38(struct Spawner *self, struct Object *target, Quadword *position, void *orientation, int *enabled);
void func_0021AB48(struct Spawner *self, struct Record *record);
void *func_0021B320(struct Spawner *self, struct Template *template, Quadword *position, void *orientation, int enabled);
void func_002413E0(void *object, float value);
void func_00241338(void *object, float value);
void func_0021ABA8(struct Spawner *self)
{
    struct Object *target;
    struct Placement place;
    target = func_001F4AD0(D_00475480, 0);
    func_001C8168(self);
    func_0021ADF8(self);
    if (!target || !func_0013B500(target, 0x58) || target->kind != 2) {
        self->nextTime = D_0036BB98.now + 5.0f;
    } else {
        struct Record *record;
        struct Template *source;
        void *spawned;
        if (D_0036BB98.now < self->nextTime) return;
        self->nextTime = D_0036BB98.now + 1.0f;
        record = func_0021AEB0(self);
        if (!record) return;
        source = func_0021AF38(self, target, &place.position, place.orientation, &place.enabled);
        if (!source) return;
        if (record->handle) func_0021AB48(self, record);
        spawned = func_0021B320(self, source, &place.position, place.orientation, place.enabled);
        if (!spawned) return;
        func_002413E0(spawned, 0.01f);
        func_00241338(spawned, 0.5f);
        record->handle = spawned;
        record->source = source;
        self->active++;
        source->claimed = 1;
        self->nextTime = D_0036BB98.now + self->interval;
    }
}
