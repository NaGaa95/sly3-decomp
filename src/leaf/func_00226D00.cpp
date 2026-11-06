// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Method { short delta; short pad; void *fn; };
union Slot { int i; unsigned u; float f; void *p; short s[2]; };
struct Record {
    unsigned type : 8;
    unsigned flag : 1;
    unsigned first : 11;
    unsigned second : 11;
    int x4;
    Slot v8;
    Slot vC;
};
struct Blob { Slot w[28]; };
struct CleanupList { void *head, *tail; int linkOffset; };
struct Table;
struct CleanupIterator { CleanupList *list; void **next; int linkOffset; CleanupIterator *previous; };
struct Activation;
struct Obj;
struct World;
struct Table {
    unsigned char pad0[0xC];
    Method * vt;  // 0xC
    unsigned char pad10[0x34];
    Record * records;  // 0x44
    CleanupList list;  // 0x48
    Activation * x54;  // 0x54
};
struct Activation {
    unsigned char pad0[0xC];
    Method * vt;  // 0xC
    unsigned char pad10[0x4];
    Table * env;  // 0x14
    unsigned char pad18[0x4];
    Obj * owner;  // 0x1C
    unsigned char pad20[0x4];
    Obj * x24;  // 0x24
    Obj * actor;  // 0x28
    Record * first;  // 0x2C
    int flag30;  // 0x30
    Record * current;  // 0x34
    float stamp;  // 0x38
    unsigned char pad3C[0x18];
    Obj * x54;  // 0x54
    Obj * x58;  // 0x58
    Obj * x5C;  // 0x5C
    Obj * x60;  // 0x60
    int x64;  // 0x64
    Obj * x68;  // 0x68
    Obj * x6C;  // 0x6C
    Record * x70;  // 0x70
    unsigned char pad74[0xC];
    int x80;  // 0x80
    int x84;  // 0x84
    unsigned char pad88[0x8];
    Obj * x90;  // 0x90
    int x94;  // 0x94
    unsigned char pad98[0x64];
    Obj * xFC;  // 0xFC
    Obj * x100;  // 0x100
    int x104;  // 0x104
    unsigned char pad108[0xC];
    int x114;  // 0x114
    int depth;  // 0x118
    Record * stack[1];  // 0x11C
    unsigned char pad120[0x3C];
    void * list;  // 0x15C
    unsigned char pad160[0x8];
    float x168;  // 0x168
    Obj * x16C;  // 0x16C
    int x170;  // 0x170
};
struct Obj {
    unsigned char pad0[0xC];
    Method * vt;  // 0xC
    unsigned char pad10[0x110];
    int x120;  // 0x120
    unsigned char pad124[0xC];
    int x130;  // 0x130
    unsigned char pad134[0x44];
    int x178;  // 0x178
    unsigned char pad17C[0x4];
    int x180;  // 0x180
    unsigned char pad184[0x34];
    int x1B8;  // 0x1B8
    unsigned char pad1BC[0xA4];
    qword x260;  // 0x260
    unsigned char pad270[0x2C];
    int x29C;  // 0x29C
    unsigned char pad2A0[0x24];
    int x2C4;  // 0x2C4
    unsigned char pad2C8[0x58];
    int x320;  // 0x320
    unsigned char pad324[0x18];
    int x33C;  // 0x33C
    unsigned char pad340[0x8];
    int x348;  // 0x348
    unsigned char pad34C[0x1B4];
    int x500;  // 0x500
    unsigned char pad504[0x4];
    int x508;  // 0x508
    int x50C;  // 0x50C
    unsigned char pad510[0x4];
    Obj * x514;  // 0x514
    unsigned char pad518[0xA48];
    int xF60;  // 0xF60
    unsigned char padF64[0xB0];
    int x1014;  // 0x1014
    unsigned char pad1018[0x4];
    Obj * x101C;  // 0x101C
    unsigned char pad1020[0x80];
    int x10A0;  // 0x10A0
    unsigned char pad10A4[0x2C];
    int x10D0;  // 0x10D0
    unsigned char pad10D4[0x34];
    Obj * x1108;  // 0x1108
    unsigned char pad110C[0x184];
    int x1290;  // 0x1290
    unsigned char pad1294[0x158];
    int x13EC;  // 0x13EC
    unsigned char pad13F0[0x4F0];
    int x18E0;  // 0x18E0
    int x18E4;  // 0x18E4
    unsigned char pad18E8[0xD0];
    Obj * x19B8;  // 0x19B8
    unsigned char pad19BC[0x34];
    int x19F0;  // 0x19F0
};
struct World {
    unsigned char pad0[0x3EB8];
    int count;  // 0x3EB8
    Obj * items[1];  // 0x3EBC
};
struct Part {
    unsigned char pad0[0xEC];
    Method * vt;  // 0xEC
};
struct Obj5D {
    unsigned char pad0[0x21C];
    Method * vt;  // 0x21C
};
struct Obj15 {
    unsigned char pad0[0x20C];
    Method * vt;  // 0x20C
};
struct Comp {
    unsigned char pad0[0x24];
    Method * vt;  // 0x24
};
struct Fx3 {
    unsigned char pad0[0xC];
    Method * vt;  // 0xC
    unsigned char pad10[0x20];
    Obj * x30;  // 0x30
    int x34;  // 0x34
    unsigned char pad38[0x20];
    int x58;  // 0x58
    int x5C;  // 0x5C
    float x60;  // 0x60
};
struct Fx4 {
    unsigned char pad0[0xC];
    Method * vt;  // 0xC
    unsigned char pad10[0x20];
    int x30;  // 0x30
    float x34;  // 0x34
    int x38;  // 0x38
    float x3C;  // 0x3C
};
struct Item {
    unsigned char pad0[0x4];
    void * x4;  // 0x4
    int x8;  // 0x8
};
struct FRAME { FRAME(); ~FRAME(); };
extern "C" {
extern CleanupIterator *D_0036AE94;
extern World D_00475480;
extern int D_0046FD00, D_0046FC30, D_00474FF0, D_0046F770, D_0036E740, D_0036C700, D_004BC228, D_004BC220, D_0036DBEC;
extern void *D_00468D04;
extern Obj *D_0036BB80;
extern qword D_00317550, D_00317560;
int func_0013B500(void *object, int kind);
Obj *func_00226770(Activation *self, int id);
Obj *func_0017E1B8(World *world, int kind, int id, void *owner);
int func_0017E208(World *world, int kind, int id, int flag, int limit, Obj **out);
int func_00226950(Activation *self, int a, int b);
Obj *func_00226348(Table *env, int key, Activation *exclude);
void func_0022B930(void *object);
Obj *func_00226BB0(Activation *self);
Obj *func_00226B78(Activation *self);
Obj *func_00226B20(Activation *self);
void func_00226AE8(Activation *self, int id);
void func_00226BE0(Activation *self);
float func_00226458(Table *env);
void func_0022B028(Activation *self, Record *node, void *object);
void func_002261A0(void *target, int id);
void func_002261F0(void *target, int id);
void func_00226050(void *target);
void func_00156578(Obj *object, int a, int b, int c);
void func_00225EE8(Obj *object, Obj *actor);
void func_0025D478(World *world, void *spec, void *owner, int mode, Activation *self, void *out);
void func_0022B718(Activation *self);
int func_00239CC0(void *p);
int func_00239E70(void *p);
void func_00222FF0(void *table, int a, int b, Obj *object);
void func_0022A430(float elapsed, Activation *self, Record *node);
void func_00185908(void *table, int a, void *p, void *owner);
void func_0022B290(Activation *self, int a, int b);
void func_0022BF08(Activation *self, int a);
int func_001569A8(void *p);
void func_001BDBB0(void *p, int a);
void func_0027FA30(Obj *object);
void func_00280010(Obj *object);
void func_0027FCC8(Obj *object);
void func_0017D7D0(Obj *object);
void func_0019E1F8(Obj *object);
void func_002775B8(Obj *object);
void func_0013BC80(Obj *object);
void func_001E8E40(Obj *object, Obj *actor);
void func_001716F8(Obj *object, Obj *actor);
void func_001B40F0(void *p, int a, void *b, void *c);
void func_001B4430(void *p, int a);
void func_0022AEC8(Activation *self, Obj *object, void *out, float *angle);
void func_00198D78(void *vec, int a, int b, float x, float y);
}
#define VCALL(o, slot, T) ((T)((o)->vt[slot].fn))
#define SELF(o, slot) ((char *)(o) + (o)->vt[slot].delta)
#define BLOB(n) ((Blob *)(n)->v8.p)
static inline Record *Resolve(Table *env, unsigned index)
{
    return index ? &env->records[index] : 0;
}
static inline void Push(Activation *self, Record *node)
{
    self->stack[self->depth++] = node;
}
static inline Record *Pop(Activation *self)
{
    return self->depth ? self->stack[--self->depth] : 0;
}
class ScopedBracket {
    Activation *activation;
public:
    ScopedBracket(Activation *a) : activation(a)
    {
        Method *entry = &activation->vt[1];
        ((void (*)(void *))entry->fn)((char *)activation + entry->delta);
    }
    ~ScopedBracket()
    {
        Method *entry = &activation->vt[2];
        ((void (*)(void *))entry->fn)((char *)activation + entry->delta);
    }
};
extern "C" {
Activation *func_0022BF40(Table *env, Record *node, Activation *self);
void func_002265E0(Activation *self);
void func_001F4B00(World *world, int a, Obj *object);
Obj *func_00137428(Obj *object, Obj *target, int a, float x, float y);
float func_0011E940(float x, float y);
void func_00154B48(Obj *actor, Obj *object);
void func_00154C80(Obj *actor, Obj *object, qword position);
void func_00154D40(Obj *actor, Obj *object);
void func_00154BA8(Obj *actor, Obj *object);
void func_00154C00(Obj *actor, Obj *object);
void func_00154EF0(Obj *actor, Obj *object, Obj *other, int a);
void func_0022EA88(Obj *handle, qword position, int a, int b, int c, void *d, void *e);
void func_001573A0(void *p);
void func_001B5170(void *p);
void func_00238568(void *list);
Obj *func_00238690(void *list, int kind);
void func_00157970(Obj *e, qword position);
void func_001C0538(Obj *actor, void *request);
Comp *func_001A2A40(Obj *object);
void *memset(void *p, int v, unsigned n);
void func_00153F68(Obj *actor, qword position, float a, float b);
Obj *func_0025D740(World *world, int a, int b, float f, void *owner, Table *env);
void func_0025D810(World *world, int a, int b, int c, void *d, void *owner, Table *env);
void func_0025D8A8(World *world, int a, int b, int c, int d, void *owner, Table *env);
int func_0017E208(World *world, int kind, int id, int flag, int limit, Obj **out);
void func_00167D38(Obj *object, int a);
void func_001A9058(void *table, int a, float f);
void func_0025D940(World *world, int a, int b, void *owner, Table *env, float f);
void func_0025DA70(World *world, int a, int b, void *owner, Table *env, float f);
void func_0025DB38(World *world, int a, int b, int c, int d, float g, float h, float i, int e, void *owner, Table *env, int *f);
void func_0025DCA8(World *world, int a, Table *env, int *p);
void func_001BDA88(void *p, int a, void *spawn);
void func_0016ADC0(Obj *o, Obj *p);
void func_0016AE00(Obj *o, Obj *p);
void func_0016AE40(Obj *o, qword a, qword b, float f);
void func_0016AE88(Obj *o, float f);
void func_0016AE90(Obj *o);
void func_001BE370(void *p, Obj *o);
void func_00221AC8(void *p, int a);
void func_0022B398(Activation *self, int a);
Obj *func_002485D8(void *p, int a, int b, Obj *c);
void func_00244F08(Obj *o, Obj *p);
void func_00245100(Obj *o, float a, float b);
void func_00244E08(Obj *o, float a);
int func_00248858(void *p, int a);
void func_00248740(void *p);
void func_0027ED18(void *p);
void func_0022B4A8(Activation *self, Obj *o, int a, int b);
void func_0022B580(Activation *self, Obj *o, int a, int b);
void func_0020A758(void *a, int b, int c, void *d);
void func_0020A880(void *a, float c, int b);
void func_00248130(void *p, int a);
void func_002482F0(void *p, int a);
void *func_0023FB68(Obj *o, int a);
void func_001E2848(Obj *actor, void *a, int b, int c, int d);
void func_0021E870(void *p, int a, float f);
void func_0021E930(void *p, int a);
void func_00198540(Obj *a, Obj *b);
void func_001985A8(Obj *a, Obj *b);
void func_001E2358(Obj *actor);
void func_001B7268(void *p, int a, int b, int c, float f);
void func_00273030(void *p, Obj *o);
void func_001528E0(Obj *actor);
void func_00168670(Obj *o, int a);
int func_001F4A80(Obj *o);
void func_0022B238(Activation *self, int a);
void func_00172C30(Obj *a, int b);
void func_00172AE8(Obj *a, int b);
void func_00241100(Obj *a, int b, int c, int d, void *e);
void *func_001D25B0(void *request);
struct Cleanup { ~Cleanup(); };
void func_002BF140(Cleanup *p, int mode);
inline Cleanup::~Cleanup() { func_002BF140(this, 2); }
void func_001634F0(Obj *a, int b, int c, void *d);
void func_0022D318(Obj *actor);
void func_001BDB50(void *p);
Obj *func_0017E1B8(World *world, int kind, int id, void *owner);
Obj *func_001FBF08(Obj *o);
Obj *func_001FBE30(Obj *o, int a);
Obj *func_001FBEC0(Obj *o);
void func_001FC060(Obj *a, Obj *b);
void func_001FC090(Obj *a, Obj *b);
void func_001FC0E0(void *a, void *b);
Obj *func_001FC118(Obj *o);
Item *func_001400C0(Obj *o, int a);
void func_001AF2A8(Obj *o, void *p, int a);
void func_001C7A00(Obj *a, Obj *b, int c);
void func_0023EBF8(Obj *a, int b);
void func_0023EC98(Obj *a, int b);
void func_0023D938(Obj *a, qword b);
void func_0023D9D0(Obj *a, qword b);
void func_0024E920(Obj *a, Obj *b);
}
union QV { qword q; float f[4]; };
struct M3 { qword r[3]; };
union M4 { struct { qword r[4]; } q; M3 m3; float af[4][4]; };
extern "C" {
M3 func_0011C8C0(qword axis, float angle);
qword *func_002BA818(qword *p, qword v);
void func_0013A678(void *list, Obj *item, Obj *target);
void func_00166548(Obj *o);
void func_0022B090(Activation *self, Obj *o);
void func_0022B150(Activation *self, Obj *o);
void func_0023DF78(Obj *o);
void func_0022B7F0(Activation *self);
}
static __inline__ qword Position(Obj *o)
{
    return ((qword *(*)(void *))(o->vt[36].fn))(SELF(o, 36))[3];
}
static __inline__ qword VAdd(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline void InitializeCleanupIterator(CleanupIterator *iterator, CleanupList *list)
{
    iterator->list = list;
    iterator->next = (void **)list;
    iterator->linkOffset = list->linkOffset;
    iterator->previous = D_0036AE94;
    D_0036AE94 = iterator;
}
static inline void *NextCleanupItem(CleanupIterator *iterator)
{
    void *item = *iterator->next;
    iterator->next = (void **)((unsigned)item + iterator->linkOffset);
    return item;
}
struct Child { unsigned char pad[0x18]; int x18; };
#define NEED_ACTOR(kind) \
    if (!self->actor) break; \
    if (!func_0013B500(self->actor, kind)) break;
extern "C" void func_00226D00(Activation *self)
{
    ScopedBracket bracket(self);
    unsigned n, counter;
    Record *current = self->current;
    if (current == self->first || (self->flag30 && current->type == 2)) {
        Record *child = Resolve(self->env, current->first);
        if (!child) {
            self->current = 0;
            return;
        }
        Push(self, current);
        self->current = child;
    } else {
        Record *next;
        while (!(next = Resolve(self->env, self->current->second))) {
            Record *popped = Pop(self);
            self->current = popped;
            switch (popped->type) {
            case 0:
            case 2:
                self->current = 0;
                return;
            case 4:
                goto exec;
            case 7:
            case 8:
            case 9:
                self->current = Pop(self);
                break;
            }
        }
        self->current = next;
    }
exec:
    Record *node = self->current;
    func_00226BE0(self);
    n = node->type;
    switch (n) {
    case 0:
        func_002265E0(func_0022BF40(self->env, node, self));
        break;
    case 4:
        if (func_00226950(self, node->v8.i, node->vC.i)) {
            Record *child = Resolve(self->env, node->first);
            if (child) {
                Push(self, node);
                self->current = child;
                goto exec;
            }
        }
        break;
    case 6: {
        Record *choice = Resolve(self->env, node->first);
        Record *child;
        if (!choice)
            break;
        do {
            if ((unsigned)(choice->type - 7) >= 2 || func_00226950(self, choice->v8.i, choice->vC.i)) {
                child = Resolve(self->env, choice->first);
                if (!child)
                    break;
                Push(self, node);
                Push(self, choice);
                self->current = child;
                goto exec;
            }
            choice = Resolve(self->env, choice->second);
        } while (choice);
        break;
    }
    case 11:
        if (node->v8.i == 0x3B) {
            CleanupIterator iterator;
            Child *item;
            InitializeCleanupIterator(&iterator, (CleanupList *)&self->env->list);
            while ((item = (Child *)NextCleanupItem(&iterator)) != 0) {
                if (item->x18)
                    func_0022B930(item);
            }
            D_0036AE94 = iterator.previous;
        } else {
            void *target = self;
            if (node->v8.i != -1)
                target = func_00226348(self->env, node->v8.i, 0);
            if (target)
                func_0022B930(target);
        }
        break;
    case 15:
    case 16: {
        void *target;
        if (node->vC.i == -1) {
            target = self->env;
        } else {
            Obj *o = func_00226770(self, node->vC.i);
            target = (o && func_0013B500(o, 0x87)) ? o : 0;
        }
        if (!target)
            break;
        if (node->type == 0xF)
            func_002261A0(target, node->v8.i);
        else
            func_002261F0(target, node->v8.i);
        break;
    }
    case 17: {
        void *target;
        if (node->v8.i == -1) {
            target = self->env;
        } else {
            Obj *o = func_00226770(self, node->v8.i);
            target = (o && func_0013B500(o, 0x87)) ? o : 0;
        }
        if (!target)
            break;
        func_00226050(target);
        break;
    }
    case 18: {
        Obj *o = func_00226770(self, node->v8.i);
        if (!o)
            break;
        if (func_0013B500(o, 0x5D)) {
            Obj5D *p = (Obj5D *)o;
            char *part = (char *)p + 0x130;
            ((void (*)(void *))p->vt[2].fn)(part + p->vt[2].delta);
        } else if (func_0013B500(o, 0x15)) {
            Obj15 *p = (Obj15 *)o;
            char *part = (char *)p + 0x120;
            ((void (*)(void *))p->vt[2].fn)(part + p->vt[2].delta);
        } else if (func_0013B500(o, 0x27)) {
            func_0027FA30(o);
        } else if (func_0013B500(o, 0x28)) {
            func_00280010(o);
        } else if (func_0013B500(o, 0x18)) {
            func_0027FCC8(o);
        } else if (func_0013B500(o, 0x8A)) {
            func_0017D7D0(o);
        } else if (func_0013B500(o, 0x4D)) {
            func_0019E1F8(o);
        } else if (func_0013B500(o, 0x71)) {
            func_002775B8(o);
        } else if (func_0013B500(o, 0x21)) {
            if (self->actor && func_0013B500(self->actor, 0x33))
                VCALL(o, 55, void (*)(void *, Obj *))(SELF(o, 55), self->actor);
        } else if (func_0013B500(o, 0x47)) {
            if (self->actor && func_0013B500(self->actor, 0x33))
                func_001E8E40(o, self->actor);
        } else if (func_0013B500(o, 0x50)) {
            if (self->actor && func_0013B500(self->actor, 0x33))
                func_001716F8(o, self->actor);
        } else {
            func_0013BC80(o);
        }
        break;
    }
    case 19: {
        Obj *o = func_00226770(self, node->v8.i);
        if (!o)
            break;
        if (!func_0013B500(o, 0x31))
            break;
        func_001F4B00(&D_00475480, node->vC.i, o);
        break;
    }
    case 20:
        self->x24 = func_00226770(self, node->x4);
        break;
    case 21: {
        void *params = &node->v8;
        self->env->x54 = self;
        VCALL(self->env, 3, void (*)(void *, int, int, int, void **, int))(SELF(self->env, 3), 4, 0, 1, &params, 0);
        self->env->x54 = 0;
        break;
    }
    case 22: {
        Obj *target = func_00226770(self, BLOB(node)->w[1].i);
        if (target) {
            if (func_0013B500(target, 0x33)) {
                func_00156578(target, BLOB(node)->w[0].i, BLOB(node)->w[2].i | 1, 5);
                if (node->flag)
                    self->x5C = target;
                break;
            }
            target = func_0013B500(target, 0x2F) ? target : 0;
        }
        Obj *source = func_00226770(self, BLOB(node)->w[0].i);
        if (!source)
            break;
        if (!func_0013B500(source, 0x82))
            break;
        Obj *made = func_00137428(source, target, BLOB(node)->w[2].i, 0.0f, 1.0f);
        if (!node->flag)
            break;
        self->x54 = made;
        VCALL(made, 1, void (*)(void *))(SELF(made, 1));
        break;
    }
    case 23: {
        Obj *o = func_00226770(self, node->v8.i);
        if (!o)
            break;
        if (!func_0013B500(o, 0x87))
            break;
        func_00225EE8(o, self->actor);
        if (node->flag)
            self->x58 = o;
        break;
    }
    case 24:
        func_00226AE8(self, node->v8.i);
        break;
    case 25: {
        struct Spec { int a, b, c, d; } spec;
        spec.a = BLOB(node)->w[0].i;
        spec.b = BLOB(node)->w[1].i;
        spec.c = BLOB(node)->w[2].i;
        spec.d = -1;
        int mode = BLOB(node)->w[3].i ? 3 : 1;
        func_0025D478(&D_00475480, &spec, self->owner, mode, self, &self->x60);
        if (!node->flag) {
            func_0022B718(self);
            break;
        }
        if (!self->x60)
            break;
        if (self->x64)
            break;
        if (func_00239CC0(self->x60))
            break;
        if (func_00239E70(self->x60) == BLOB(node)->w[2].i)
            self->x64 = 1;
        break;
    }
    case 26:
    case 27: {
        Obj *o = func_0017E1B8(&D_00475480, 0x405, node->v8.i, 0);
        if (!o)
            break;
        if (!func_0013B500(o, 0x9E))
            break;
        if (node->type == 0x1A) {
            VCALL(o, 53, void (*)(void *, int))(SELF(o, 53), node->vC.i);
            if (node->flag)
                self->x6C = o;
            break;
        }
        VCALL(o, 54, void (*)(void *))(SELF(o, 54));
        break;
    }
    case 28: {
        if (node->vC.i == 1) {
            if ((D_0036DBEC >> 1) & 1)
                break;
        }
        Obj *o = func_0017E1B8(&D_00475480, 0x405, node->v8.i, 0);
        if (!o)
            break;
        if (!func_0013B500(o, 0x9E))
            break;
        func_00222FF0(&D_0046FD00, node->vC.i, 0, o);
        break;
    }
    case 29:
        func_0022A430(0.0f, self, node);
        break;
    case 30:
        func_00185908(&D_0036C700, 1, &node->v8, self->owner);
        break;
    case 31:
        func_0022B290(self, node->v8.i, node->vC.i);
        break;
    case 33:
        func_0022BF08(self, node->v8.i);
        break;
    case 34: {
        Obj *o = func_00226770(self, node->v8.i);
        Obj *actor = 0;
        if (self->actor && func_0013B500(self->actor, 0x33)) {
            actor = self->actor;
            if (func_001569A8(actor))
                func_001BDBB0(&actor->xF60, -1);
        }
        if (o && func_0013B500(o, 0x27)) {
            func_0027FA30(o);
            break;
        }
        if (!self->actor)
            break;
        if (o && func_0013B500(o, 0x19)) {
            if (!actor)
                break;
            Obj *src = o;
            o = (Obj *)&actor->x500;
            func_001B40F0(o, 8, src, &src->x120);
            func_001B4430(o, 9);
        } else {
            QV pos;
            float angle;
            func_0022AEC8(self, o, &pos, &angle);
            if (node->vC.s[1])
                func_00198D78(&pos, 0, 0, 100.0f, -350.0f);
            M4 m4;
            M4 *pm4;
            {
                M3 rot = func_0011C8C0(D_00317550, angle);
                pm4 = &m4;
                func_002BA818(&pm4->q.r[3], pos.q);
                pm4->q.r[0] = rot.r[0];
                pm4->q.r[1] = rot.r[1];
                pm4->q.r[2] = rot.r[2];
                m4.af[2][3] = 0.0f;
                m4.af[1][3] = 0.0f;
                m4.af[0][3] = 0.0f;
                pm4->af[3][3] = 1.0f;
            }
            VCALL(self->actor, 43, void (*)(void *, int, M4 *))(SELF(self->actor, 43), 0, pm4);
            if (!actor)
                break;
            if (node->vC.s[0] == 0) {
                if (actor->x13EC == 0) {
                    func_001B7268(&actor->x320, 0xB, 0, 0, 1.0f);
                    func_0023DF78(actor);
                }
            }
        }
        func_0022B028(self, 0, 0);
        break;
    }
    case 35:
        func_00166548(func_00226B20(self));
        break;
    case 36: {
        Obj *o = func_00226770(self, node->v8.i);
        if (!o)
            break;
        if (!func_0013B500(o, 0xE))
            break;
        func_0022B090(self, o);
        break;
    }
    case 37:
        func_0022B150(self, func_00226770(self, node->v8.i));
        break;
    case 38: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        if (actor->x1014 == -1)
            break;
        QV pos;
        func_0022AEC8(self, func_00226770(self, node->v8.i), &pos, 0);
        func_0022EA88(actor->x101C, pos.q, 0, 0, 0, 0, &self->x84);
        func_0022B028(self, node, actor);
        break;
    }
    case 40: {
        NEED_ACTOR(0x33)
        if (node->vC.i == -1)
            break;
        Obj *item = func_0017E1B8(&D_00475480, 1, node->vC.i, self->actor);
        if (!item)
            break;
        Obj *target = func_00226770(self, node->v8.i);
        if (!target) {
            if (node->v8.i != -1)
                break;
        }
        func_0013A678(&self->actor->x10D0, item, target);
        break;
    }
    case 41: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        func_00154B48(actor, func_00226770(self, node->v8.i));
        func_0022B028(self, node, actor);
        break;
    }
    case 42: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        Obj *first = func_00226770(self, node->v8.i);
        Obj *second = func_00226770(self, node->vC.i);
        func_00154C80(actor, first, Position(second));
        func_0022B028(self, node, actor);
        break;
    }
    case 43: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        func_00154D40(actor, func_00226770(self, node->v8.i));
        func_0022B028(self, node, actor);
        break;
    }
    case 44: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        func_00154BA8(actor, func_00226770(self, node->v8.i));
        break;
    }
    case 45: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        func_00154C00(actor, func_00226770(self, node->v8.i));
        func_0022B028(self, node, actor);
        break;
    }
    case 46: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        Obj *made = func_0017E1B8(&D_00475480, 1, BLOB(node)->w[0].i, actor);
        Obj *other;
        if (BLOB(node)->w[1].i == 3)
            other = func_00226B20(self);
        else
            other = func_00226770(self, BLOB(node)->w[1].i);
        func_00154EF0(actor, made, other, BLOB(node)->w[2].i);
        func_0022B028(self, node, actor);
        break;
    }
    case 47:
        self->x168 = func_0011E940(BLOB(node)->w[0].f, BLOB(node)->w[1].f);
        if (!func_00226770(self, BLOB(node)->w[2].i))
            break;
        NEED_ACTOR(0x33)
        func_0022B028(self, node, self->actor);
        break;
    case 48: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        if (BLOB(node)->w[3].i != -1) {
            func_00156578(actor, BLOB(node)->w[3].i, 9, 6);
            if (node->flag)
                self->x5C = actor;
        }
        Obj *target = func_00226770(self, BLOB(node)->w[0].i);
        if (target) {
            if (func_0013B500(target, 0x20) || func_0013B500(target, 0xB) || func_0013B500(target, 0x24) ||
                func_0013B500(target, 0x64) || func_0013B500(target, 0xA) || func_0013B500(target, 0x26))
                func_001B5170(&actor->x500);
            if (actor->x50C != -1) {
                if (actor->x508 == 3) {
                    Obj *handle = actor->x514;
                    QV pos;
                    func_0022AEC8(self, target, &pos, 0);
                    func_0022EA88(handle, pos.q, 0, 0, 0, &self->x80, 0);
                }
            }
        }
        func_001573A0(&actor->x10A0);
        func_0022B028(self, node, actor);
        break;
    }
    case 49:
        self->x104 = 1;
        break;
    case 50:
        self->x104 = 0;
        break;
    case 51: {
        NEED_ACTOR(0x33)
        Obj *source = func_00226770(self, BLOB(node)->w[0].i);
        if (!source)
            break;
        if (!func_0013B500(source, 9))
            break;
        Obj *actor = self->actor;
        void *list = &actor->x29C;
        func_00238568(list);
        VCALL(actor, 99, void (*)(void *, int))(SELF(actor, 99), 0);
        if (BLOB(node)->w[4].i != -1) {
            func_00156578(actor, BLOB(node)->w[4].i, 9, 6);
            self->x5C = actor;
        }
        Fx3 *e = (Fx3 *)func_00238690(list, 0xF3);
        e->x30 = source;
        e->x58 = self->x104;
        e->x34 = BLOB(node)->w[1].i;
        e->x5C = BLOB(node)->w[2].i;
        e->x60 = BLOB(node)->w[3].f;
        VCALL(e, 8, void (*)(void *))(SELF(e, 8));
        break;
    }
    case 52: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        void *list = &actor->x29C;
        func_00238568(list);
        VCALL(actor, 99, void (*)(void *, int))(SELF(actor, 99), 0);
        QV pos;
        func_0022AEC8(self, func_00226770(self, BLOB(node)->w[0].i), &pos, 0);
        if (BLOB(node)->w[4].i != -1) {
            func_00156578(actor, BLOB(node)->w[4].i, 9, 6);
            self->x5C = actor;
        }
        Fx4 *e = (Fx4 *)func_00238690(list, 0xF4);
        e->x30 = self->x104;
        e->x34 = BLOB(node)->w[1].f;
        e->x38 = BLOB(node)->w[2].i;
        e->x3C = BLOB(node)->w[3].f;
        func_00157970((Obj *)e, pos.q);
        VCALL(e, 8, void (*)(void *))(SELF(e, 8));
        break;
    }
    case 53: {
        NEED_ACTOR(0x33)
        Obj *actor = self->actor;
        if (actor->x50C == -1)
            break;
        if (actor->x508 != 8)
            break;
        func_0022B028(self, node, actor);
        break;
    }
    case 54: {
        NEED_ACTOR(0x33)
        struct Req {
            Obj *id;
            Comp *comp;
            int pad[2];
            qword pos;
        } req;
        Obj *actor = self->actor;
        Obj *target = func_00226770(self, BLOB(node)->w[0].i);
        memset(&req, 0, 0x20);
        if (!target) {
            req.pos = VAdd(Position(actor), actor->x260);
        } else {
            Comp *c = func_001A2A40(target);
            req.comp = c;
            if (c) {
                if (actor->x1014 != -1) {
                    if (actor->x101C == target)
                        break;
                }
                VCALL(c, 2, void (*)(void *, Obj *, void *))(SELF(c, 2), actor, &req.pos);
                req.id = target;
            } else {
                func_0022AEC8(self, target, &req.pos, 0);
                if (BLOB(node)->w[3].i)
                    func_00198D78(&req.pos, 0, 0, 100.0f, -350.0f);
            }
        }
        func_001C0538(actor, &req);
        if (BLOB(node)->w[1].i == 1)
            actor->x348 = 0;
        if (func_0013B500(actor, 0x34))
            actor->x19F0 = BLOB(node)->w[2].i;
        func_0022B028(self, node, actor);
        break;
    }
    case 55: {
        NEED_ACTOR(0x33)
        QV pos;
        Obj *a = func_00226770(self, BLOB(node)->w[0].i);
        Obj *actor = self->actor;
        func_0022AEC8(self, a, &pos, 0);
        func_00153F68(actor, pos.q, BLOB(node)->w[1].f, BLOB(node)->w[2].f);
        break;
    }
    case 56:
    case 57: {
        Obj *o = func_0025D740(&D_00475480, node->type == 0x38, node->v8.i, node->vC.f, self->owner, self->env);
        if (!o)
            break;
        if (!node->flag)
            break;
        if (func_0013B500(o, 0x2F))
            self->x68 = o;
        break;
    }
    case 58:
    case 59: {
        Obj *owner = 0;
        int mode = node->type == 0x3A;
        if (self->owner) {
            if (func_0013B500(self->owner, 0x2F))
                owner = self->owner;
        }
        func_0025D810(&D_00475480, mode, node->v8.i, node->vC.i, owner, self->owner, self->env);
        break;
    }
    case 60:
    case 61:
        func_0025D8A8(&D_00475480, node->type == 0x3C, node->v8.i, node->vC.i, 0, self->owner, self->env);
        break;
    case 62: {
        Obj *list[256];
        int count = func_0017E208(&D_00475480, 0x505, node->v8.i, 0, 0x100, list);
        int i;
        for (i = 0; i < count; i++)
            VCALL(list[i], 9, void (*)(void *))(SELF(list[i], 9));
        break;
    }
    case 63: {
        for (counter = 0; (int)counter < D_00475480.count; counter++)
            func_00167D38(D_00475480.items[counter], node->v8.i);
        break;
    }
    case 64:
        func_001A9058(&D_0036E740, node->vC.i, node->v8.f);
        break;
    case 65:
        func_0025D940(&D_00475480, BLOB(node)->w[0].i, BLOB(node)->w[1].i, self->owner, self->env, BLOB(node)->w[2].f);
        break;
    case 66:
        func_0025DA70(&D_00475480, BLOB(node)->w[0].i, BLOB(node)->w[1].i, self->owner, self->env, BLOB(node)->w[2].f);
        break;
    case 67:
        func_0025DB38(&D_00475480, BLOB(node)->w[0].i, BLOB(node)->w[1].i, BLOB(node)->w[2].i, BLOB(node)->w[3].i, BLOB(node)->w[4].f, BLOB(node)->w[5].f, BLOB(node)->w[6].f, 0, self->owner, self->env, &self->x114);
        break;
    case 68:
        func_0025DCA8(&D_00475480, node->v8.i, self->env, &self->x114);
        break;
    case 70: {
        union Params { qword q[5]; struct { unsigned char pad[0x30]; Obj *c; Obj *d; int e[2]; } f; };
        struct Spawn { Obj *a; Obj *b; int pad[2]; Params params; } spawn;
        spawn.a = func_00226770(self, BLOB(node)->w[1].i);
        if (spawn.a)
            func_0013B500(spawn.a, 0x32);
        spawn.b = func_0017E1B8(&D_00475480, 0x405, BLOB(node)->w[26].i, 0);
        spawn.params = *(Params *)&BLOB(node)->w[4];
        spawn.params.f.c = func_00226770(self, BLOB(node)->w[24].i);
        spawn.params.f.d = func_00226770(self, BLOB(node)->w[25].i);
        Obj *actor = func_00226770(self, BLOB(node)->w[0].i);
        if (!actor)
            break;
        if (!func_0013B500(actor, 0x33))
            break;
        if (actor->x130 == -1)
            break;
        if (self->x90)
            break;
        self->x90 = actor;
        func_001BDA88(&actor->xF60, 1, &spawn);
        break;
    }
    case 71:
        func_0022B7F0(self);
        break;
    case 72: {
        Obj *o = func_00226BB0(self);
        if (!o)
            break;
        func_0016ADC0(o, func_00226770(self, node->v8.i));
        break;
    }
    case 73: {
        Obj *o = func_00226BB0(self);
        if (!o)
            break;
        func_0016AE00(o, func_00226770(self, node->v8.i));
        break;
    }
    case 74: {
        Obj *o = func_00226BB0(self);
        if (!o)
            break;
        func_0016AE40(o, *(qword *)&BLOB(node)->w[0], *(qword *)&BLOB(node)->w[4], BLOB(node)->w[8].f);
        break;
    }
    case 75: {
        Obj *o = func_00226BB0(self);
        if (!o)
            break;
        func_0016AE88(o, node->v8.f);
        break;
    }
    case 76: {
        Obj *o = func_00226BB0(self);
        if (!o)
            break;
        func_0016AE90(o);
        break;
    }
    case 77: {
        Obj *o = func_00226770(self, node->v8.i);
        Obj *list = func_00226B78(self);
        if (!o)
            break;
        if (!func_0013B500(o, 0x32))
            break;
        if (!list)
            break;
        func_001BE370(&list->xF60, o);
        break;
    }
    case 78:
        D_004BC228 = node->v8.i & 0xF0;
        break;
    case 80:
        func_00221AC8(&D_0046FC30, 0);
        break;
    case 82: {
        func_0022B398(self, node->v8.i);
        Obj *actor = node->x4 != -1 ? self->actor : 0;
        Obj *o = func_002485D8(&D_00474FF0, BLOB(node)->w[7].i, BLOB(node)->w[0].i, actor);
        if (o) {
            func_00244F08(o, func_00226770(self, BLOB(node)->w[1].i));
            func_00245100(o, (float)BLOB(node)->w[2].i, (float)BLOB(node)->w[3].i);
            func_00244E08(o, BLOB(node)->w[4].f);
        }
        self->x70 = node;
        break;
    }
    case 83: {
        struct Ids { int pad[7]; int ids[1]; };
        int i = 0;
        if (!BLOB(node)->w[5].i)
            goto zero83;
    again83:
        if (i >= BLOB(node)->w[5].i)
            break;
        if (!func_00248858(&D_00474FF0, ((Ids *)BLOB(node))->ids[i]))
            goto next83;
        func_00248740(&D_00474FF0);
        break;
    zero83:
        func_00248740(&D_00474FF0);
        break;
    next83:
        i++;
        goto again83;
    }
    case 84:
        func_0027ED18(&D_004BC220);
        break;
    case 85:
        if (!self->actor)
            break;
        func_0022B4A8(self, self->actor, node->v8.i, node->vC.i);
        break;
    case 86:
        if (!self->actor)
            break;
        func_0022B580(self, self->actor, node->v8.i, node->vC.i);
        break;
    case 87: {
        struct Entry { float f; int x; unsigned char pad[0x28]; } entries[10];
        n = 0;
        Record *c;
        if (!D_00468D04)
            break;
        for (c = Resolve(self->env, node->second); c && c->type != 0x57; c = Resolve(self->env, c->second)) {
            if (c->type == 0x58) {
                if (n < 10) {
                    Entry *e = &entries[n];
                    e->f = c->v8.f;
                    e->x = c->vC.i;
                    n++;
                }
            }
        }
        func_0020A758(D_00468D04, node->v8.i, n, entries);
        break;
    }
    case 88:
        if (!D_00468D04)
            break;
        func_0020A880(D_00468D04, node->v8.f, node->vC.i);
        break;
    case 89:
        func_00248130(&D_00474FF0, node->v8.i);
        break;
    case 90:
        func_002482F0(&D_00474FF0, node->v8.i);
        break;
    case 92: {
        NEED_ACTOR(0x35)
        Obj *actor = self->actor;
        Obj *o = func_00226770(self, BLOB(node)->w[0].i);
        if (!o)
            break;
        void *r = func_0023FB68(o, -1);
        if (!r)
            break;
        func_001E2848(actor, r, BLOB(node)->w[2].i, BLOB(node)->w[1].i, BLOB(node)->w[3].i);
        break;
    }
    case 93:
    case 94:
        NEED_ACTOR(0x36)
        func_0022B028(self, node, self->actor);
        break;
    case 96:
        func_0021E870(&D_0046F770, node->v8.i, node->vC.f);
        break;
    case 97:
        func_0021E930(&D_0046F770, node->v8.i);
        break;
    case 98: {
        Obj *a = func_00226770(self, node->v8.i);
        Obj *b = func_00226770(self, node->vC.i);
        func_00198540(a, b);
        if (!node->flag)
            break;
        self->xFC = a;
        self->x100 = b;
        break;
    }
    case 99: {
        Obj *a = func_00226770(self, node->v8.i);
        Obj *b = 0;
        if (node->vC.i != -1)
            b = func_00226770(self, node->vC.i);
        func_001985A8(a, b);
        break;
    }
    case 100:
        NEED_ACTOR(0x35)
        func_001E2358(self->actor);
        break;
    case 101: {
        NEED_ACTOR(0x36)
        Obj *actor = self->actor;
        Obj *o = func_00226770(self, node->v8.i);
        if (!o)
            break;
        if (!func_0013B500(o, 0x35))
            break;
        func_001B7268(&actor->x320, actor->x33C == 0x12 ? 3 : 1, 0, 0, 1.0f);
        func_0022B028(self, node, actor);
        break;
    }
    case 102: {
        NEED_ACTOR(0x35)
        Obj *actor = self->actor;
        if (actor->x18E4 >= 7)
            break;
        if (actor->x18E4 < 4)
            break;
        Obj *o = func_00226770(self, node->v8.i);
        if (!o)
            break;
        func_00273030(&actor->x18E0, o);
        break;
    }
    case 103: {
        NEED_ACTOR(0x35)
        Obj *actor = self->actor;
        if (actor->x18E4 >= 7)
            break;
        if (actor->x18E4 < 4)
            break;
        self->x94 = actor->x18E0;
        Obj *o = func_00226770(self, node->v8.i);
        if (!o)
            break;
        func_00273030(&actor->x18E0, o);
        func_0022B028(self, node, actor);
        break;
    }
    case 104: {
        Obj *o = func_00226770(self, node->v8.i);
        if (!o)
            break;
        if (!func_0013B500(o, 0x18))
            break;
        if (node->vC.i != -1)
            o->x178 = node->vC.i;
        func_0027FCC8(o);
        break;
    }
    case 105:
        if (!self->actor)
            break;
        if (func_0013B500(self->actor, 0x33)) {
            func_001528E0(self->actor);
            break;
        }
        if (!func_0013B500(self->actor, 0x31))
            break;
        func_00168670((Obj *)func_001F4A80(self->actor), 0);
        break;
    case 106: {
        NEED_ACTOR(0x33)
        func_0022B238(self, 0);
        self->x170 = 1;
        Obj *actor = self->actor;
        if (!actor->x1108)
            break;
        func_00172C30(actor->x1108, node->v8.i);
        func_00172AE8(actor->x1108, node->v8.i);
        break;
    }
    case 107: {
        void *s0;
        if (BLOB(node)->w[4].i == -1)
            s0 = self->env;
        else
            s0 = func_00226770(self, BLOB(node)->w[4].i);
        Obj *a0 = func_00226770(self, BLOB(node)->w[0].i);
        if (!s0)
            break;
        if (!a0)
            break;
        func_00241100(a0, BLOB(node)->w[1].i, BLOB(node)->w[2].i, BLOB(node)->w[3].i, s0);
        break;
    }
    case 108: {
        static const int kFlags[3] = {0x80, 0x10, 0x20};
        struct Request { int size; int alignment; } request;
        struct Pair { int id; int flags; };
        struct Link { int key; Record *owner; Link *next; };
        int i, count;
        Pair *buffer, *out;
        Request *r;
        if (!D_0036BB80)
            break;
        count = BLOB(node)->w[1].i;
        i = 0;
        FRAME frame;
        counter = 0;
        r = &request;
        r->size = count * 8;
        r->alignment = 16;
        buffer = (Pair *)func_001D25B0(r);
        if (count > 0) {
            out = buffer;
            for (; i < count && counter < 3; i++) {
                Cleanup cleanup;
                int id = ((int *)BLOB(node)->w[2].p)[i];
                int exists = 0;
                for (Link *e = (Link *)self->list; e; e = e->next) {
                    if (e->key == id && e->owner == node) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists) {
                    out->id = id;
                    out->flags = kFlags[counter++];
                    out++;
                }
            }
        }
        self->x16C = D_0036BB80;
        func_001634F0(D_0036BB80, BLOB(node)->w[0].i, counter, buffer);
        break;
    }
    case 115: {
        static const int kIds[3] = {0x80, 0x10, 0x20};
        struct Pair { int id; int flags; } buffer[3];
        int i, n;
        if (!D_0036BB80)
            break;
        n = 0;
        for (i = 0; i < 3; i++) {
            buffer[n].id = -1;
            buffer[n].flags = kIds[i];
            n++;
        }
        self->x16C = D_0036BB80;
        func_001634F0(D_0036BB80, -1, n, buffer);
        break;
    }
    case 109:
        NEED_ACTOR(0x37)
        func_0022D318(self->actor);
        break;
    case 110:
        NEED_ACTOR(0x33)
        func_001BDB50(&self->actor->xF60);
        break;
    case 111: {
        Obj *o = func_0017E1B8(&D_00475480, 4, node->v8.i, self->owner);
        if (!o)
            break;
        if (!func_0013B500(o, 8))
            break;
        Obj *base = o;
        if (node->vC.i & 1)
            o = func_001FBF08(o);
        else
            o = func_001FBE30(o, 0);
        if (!o)
            break;
        if (!(node->vC.i & 2))
            break;
        func_001FC060(base, o);
        break;
    }
    case 112: {
        Obj *o = func_0017E1B8(&D_00475480, 4, node->v8.i, self->owner);
        if (!o)
            break;
        if (!func_0013B500(o, 8))
            break;
        Obj *base = o;
        o = func_001FBEC0(o);
        if (!o)
            break;
        if (node->vC.i & 1)
            func_001FC090(base, o);
        func_001FC0E0(base, o);
        break;
    }
    case 113:
    case 114: {
        Obj *o = func_0017E1B8(&D_00475480, 4, node->v8.i, self->owner);
        if (!o)
            break;
        if (!func_0013B500(o, 8))
            break;
        Obj *base = o;
        o = func_001FBEC0(o);
        if (!o)
            break;
        if (node->type == 0x71)
            func_001FC060(base, o);
        else
            func_001FC090(base, o);
        break;
    }
    case 116: {
        NEED_ACTOR(0x36)
        Obj *actor = self->actor;
        Item *item = func_001400C0(actor, 0xD);
        if (item->x8) {
            func_001FC0E0(item->x4, (void *)item->x8);
            func_001AF2A8(actor, item, 0);
        }
        if (actor->x19B8)
            func_001FC0E0(func_001FC118(actor->x19B8), actor->x19B8);
        VCALL(actor, 114, void (*)(void *, int))(SELF(actor, 114), 0xD);
        Obj *o = func_00226770(self, node->v8.i);
        if (o)
            func_00273030(&actor->x1290, o);
        else
            VCALL(actor, 114, void (*)(void *, int))(SELF(actor, 114), 0xD);
        break;
    }
    case 117: {
        Obj *a = func_00226770(self, BLOB(node)->w[0].i);
        if (!a)
            break;
        Obj *b = func_00226770(self, BLOB(node)->w[1].i);
        Obj *c = (b && func_0013B500(b, 0x2F)) ? b : 0;
        func_001C7A00(a, c, BLOB(node)->w[2].i);
        break;
    }
    case 118: {
        Obj *t = func_00226770(self, BLOB(node)->w[0].i);
        if (!t)
            break;
        if (!func_0013B500(t, 0x2F))
            break;
        Obj *p5 = 0;
        Obj *p4 = 0;
        if (func_0013B500(t, 0x31)) {
            p5 = t;
            if (func_0013B500(t, 0x32))
                p4 = t;
        }
        if (BLOB(node)->w[1].i != -1)
            func_0023EBF8(t, BLOB(node)->w[1].i);
        if (BLOB(node)->w[2].i != -1)
            func_0023EC98(t, BLOB(node)->w[2].i);
        if (BLOB(node)->w[3].i != -1) {
            if (p4)
                p4->x1B8 = BLOB(node)->w[3].i;
        }
        if (BLOB(node)->w[4].i & 3) {
            if (p5) {
                if (BLOB(node)->w[4].i & 1)
                    p5->x180 = 1;
                else
                    p5->x180 = 0;
            }
        }
        if (BLOB(node)->w[4].i & 0xC) {
            if (p4) {
                if (BLOB(node)->w[4].i & 4)
                    p4->x2C4 = 1;
                else
                    p4->x2C4 = 0;
            }
        }
        if (BLOB(node)->w[4].i & 0x10) {
            func_0023D938(t, D_00317560);
            func_0023D9D0(t, D_00317560);
        }
        break;
    }
    case 119: {
        NEED_ACTOR(0x32)
        Obj *actor = self->actor;
        Obj *o = func_00226770(self, node->v8.i);
        if (!o)
            break;
        func_0024E920(actor, o);
        break;
    }
    }
    self->stamp = func_00226458(self->env);
}
