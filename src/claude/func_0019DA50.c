// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef struct VirtualEntry { short adjustment; short reserved; void (*call)(); } VirtualEntry;
struct Link { unsigned char pad[0x30]; int id; };
struct Self {
    unsigned char opaque0[12]; VirtualEntry *vtable;
    unsigned char pad10[0x19C - 0x10]; int id; struct Link *link;
    unsigned char pad1A4[0x1F8 - 0x1A4]; int open; int lit;
    unsigned char pad200[0x234 - 0x200]; float angle; unsigned char pad238[8]; qword dir;
};
struct Msg { int id; float value; int code; };
extern qword D_00317550;
void func_001F4278(struct Self *self, int msg, struct Msg *m);
M3 *func_0011C8C0(M3 *m, float angle, qword axis);
qword func_0024F278(struct Self *self, int id, float value);
void func_0019DA50(struct Self *self, int msg, struct Msg *m)
{
    func_001F4278(self, msg, m);
    if (msg != 10) return;
    if (m->id != self->id) {
        struct Link *link = self->link;
        if (!link) return;
        if (m->id != link->id) return;
    }
    switch (m->code) {
    case 0x17F: {
        M3 copy, rot;
        qword v, d;
        VirtualEntry *entry;
        func_0011C8C0(&rot, self->angle, D_00317550);
        copy = rot;
        v = func_0024F278(self, m->id, m->value);
        __asm__("vmulax.xyz $ACC,%2,%1x\n\tvmadday.xyz $ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z"
            : "=j"(d) : "j"(v), "j"(copy.r[0]), "j"(copy.r[1]), "j"(copy.r[2]));
        self->dir = d;
        entry = &self->vtable[40];
        ((void (*)(void *, qword))entry->call)((char *)self + entry->adjustment, d);
        break;
    }
    case 0x40: self->open = 1; break;
    case 0x41: self->open = 0; break;
    case 0x42: self->lit = 1; break;
    case 0x43: self->lit = 0; break;
    }
}
