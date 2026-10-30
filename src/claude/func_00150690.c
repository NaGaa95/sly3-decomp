// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta, reserved; void (*call)(void *); };
struct Obj { char pad[0xC]; struct VirtualEntry *table; int f10; int pad14; int f18; char pad1C[0x2F - 0x1C]; unsigned long flags : 8; };
struct Factory { char pad[0x10]; struct Obj *(*create)(void); };
extern struct Factory D_003409E0[];
extern char D_00475480[];
void *func_00249B78(void *g, int a, struct Obj *o);
void __as__12EvalFrameRefP9EvalFrame(struct Obj *o, void *ref);
void *func_0017DBA8(void *g, int a);
void *func_0017DBD0(void *g, int a);
void func_0011AD80(void *list, struct Obj *o);
int func_001C8610(struct Obj *o);

struct Obj *func_00150690(int kind, int a, int b, int c)
{
    struct Factory *f = &D_003409E0[kind];
    struct Obj *o = f->create();
    char *g = D_00475480;
    o->f10 = a;
    o->f18 = b;
    __as__12EvalFrameRefP9EvalFrame(o, func_00249B78(g, c, o));
    func_0011AD80(func_0017DBA8(g, b), o);
    func_0011AD80(func_0017DBD0(g, kind), o);
    o->table[7].call((char *)o + o->table[7].delta);
    if (o->flags & 1)
        o->table[11].call((char *)o + o->table[11].delta);
    if (func_001C8610(o))
        o->table[25].call((char *)o + o->table[25].delta);
    {
        struct Obj **pp = *(struct Obj ***)(g + 0x3F14);
        if (pp) {
            *pp = o;
            *(struct Obj ***)(g + 0x3F14) = pp + 1;
        }
    }
    return o;
}
