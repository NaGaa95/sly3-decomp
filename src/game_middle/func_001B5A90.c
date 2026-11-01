// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef unsigned long u64;
struct Method { short adjustment, reserved; qword *(*function)(void *); };
struct Table { unsigned char pad0[0x120]; struct Method position; };
struct Path {
    unsigned char pad0[0xC]; struct Table *table;
    unsigned char pad10[0xDC - 0x10]; int blocked;
    unsigned char padE0[0x11C - 0xE0]; float limit;
    unsigned char pad120[0x180 - 0x120]; float scale;
    unsigned char pad184[0x18C - 0x184]; int held;
};
struct Info { unsigned char pad0[0x40]; int word40; unsigned char pad44[0x4C - 0x44]; unsigned char *flags; unsigned char pad50[0x60 - 0x50]; qword word60; };
struct Actor {
    unsigned char pad0[0xC]; struct Table *table;
    unsigned char pad10[0x218 - 0x10]; struct Info *info;
    unsigned char pad21C[0xA20 - 0x21C]; unsigned char sub[0x1164 - 0xA20]; int word1164;
};
struct Control {
    struct Actor *actor;
    unsigned char pad4[4];
    int mode;
    unsigned char padC[0x14 - 0xC];
    struct Path *path;
    int id;
    float progress;
    float value;
};
int func_0013B500(void *object, int id);
int func_001BADC0(struct Actor *actor);
void func_001C0DA8(void *sub, int id, float value);
void func_001C0F18(void *sub, int word, qword vector);
float func_001205C8(qword vector);
typedef union { qword q; float f[4]; } QV;
static inline qword Sub(qword a, qword b) { __asm__("vsub.xyzw %0,%0,%1" : "+j"(a) : "j"(b)); return a; }
void func_001B5A90(struct Control *control)
{
    float scale;
    switch (control->mode) {
    case 3:
        if (control->path->held)
            return;
        func_001C0DA8(control->actor->sub, control->id, control->value);
        return;
    case 4:
        if (control->path->blocked)
            return;
        func_001C0DA8(control->actor->sub, control->id, 0.0f);
        return;
    case 0:
    case 13:
        if (func_0013B500(control->path, 0xB)) {
            if (control->path->held)
                return;
            func_001C0DA8(control->actor->sub, control->id, control->value);
            return;
        }
        if (func_0013B500(control->path, 0x24)) {
            if (control->path->blocked)
                return;
            func_001C0DA8(control->actor->sub, control->id, 0.0f);
            return;
        }
        if (func_0013B500(control->path, 0x20)) {
            if (control->path->blocked)
                return;
            scale = control->path->limit;
        } else {
            scale = control->path->scale;
        }
        {
            struct Method *first = &control->actor->table->position;
            struct Method *second;
            qword from = first->function((char *)control->actor + first->adjustment)[3];
            QV difference;
            float reach;
            second = &control->path->table->position;
            difference.q = Sub(from, second->function((char *)control->path + second->adjustment)[3]);
            reach = func_001205C8(difference.q) * scale;
            func_001C0DA8(control->actor->sub, control->id, reach);
        }
        return;
    default:
        if (!func_001BADC0(control->actor))
            return;
        if (*(u64 *)(control->actor->info->flags + 0x120) & 0x2000000000000000UL)
            return;
        if (control->actor->word1164)
            return;
        func_001C0F18(control->actor->sub, control->actor->info->word40, control->actor->info->word60);
        return;
    }
}
