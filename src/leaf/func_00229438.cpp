// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-expensive-optimizations
typedef int qword __attribute__((mode(TI)));
struct Method { short delta; short pad; void *fn; };
struct Env;
struct Obj;
struct Node;
struct Flags64 { unsigned long first : 1; unsigned long rest : 63; };
struct Arena { int storage[4]; };
struct Request { int size; int alignment; int pad[2]; };
struct Ctx {
    unsigned char pad00[0x14 - 0x0];
    Env * env;  // 0x14
    unsigned char pad18[0x1C - 0x18];
    int x1C;  // 0x1C
    unsigned char pad20[0x28 - 0x20];
    Obj * actor;  // 0x28
    Obj * x2C;  // 0x2C
    unsigned char pad30[0x38 - 0x30];
    float stamp;  // 0x38
    unsigned char pad3C[0x4C - 0x3C];
    Obj * obj;  // 0x4C
    unsigned char pad50[0x54 - 0x50];
    Obj * x54;  // 0x54
    Obj * x58;  // 0x58
    Obj * x5C;  // 0x5C
    Obj * x60;  // 0x60
    int x64;  // 0x64
    Obj * x68;  // 0x68
    Obj * x6C;  // 0x6C
    unsigned char pad70[0x84 - 0x70];
    float x84;  // 0x84
    float x88;  // 0x88
    unsigned char pad8C[0x94 - 0x8C];
    Obj * x94;  // 0x94
    unsigned char pad98[0xFC - 0x98];
    void * xFC;  // 0xFC
    void * x100;  // 0x100
    unsigned char pad104[0x108 - 0x104];
    int x108;  // 0x108
    unsigned char pad10C[0x15C - 0x10C];
    int x15C;  // 0x15C
    unsigned char pad160[0x168 - 0x160];
    float x168;  // 0x168
    Obj * x16C;  // 0x16C
};
struct Obj {
    unsigned char pad00[0x4 - 0x0];
    int x4;  // 0x4
    unsigned char pad08[0xC - 0x8];
    Method * vt;  // 0xC
    unsigned char pad10[0x28 - 0x10];
    unsigned long flags;  // 0x28
    unsigned char pad30[0x34 - 0x30];
    Node * x34;  // 0x34
    unsigned char pad38[0x48 - 0x38];
    int x48;  // 0x48
    unsigned char pad4C[0x60 - 0x4C];
    Flags64 flags60;  // 0x60
    unsigned char pad68[0x104 - 0x68];
    float x104;  // 0x104
    int x108;  // 0x108
    unsigned char pad10C[0x190 - 0x10C];
    int x190;  // 0x190
    unsigned char pad194[0x198 - 0x194];
    int x198;  // 0x198
    unsigned char pad19C[0x29C - 0x19C];
    int x29C;  // 0x29C
    unsigned char pad2A0[0x2DC - 0x2A0];
    void * x2DC;  // 0x2DC
    unsigned char pad2E0[0x33C - 0x2E0];
    int x33C;  // 0x33C
    unsigned char pad340[0x508 - 0x340];
    int x508;  // 0x508
    int x50C;  // 0x50C
    unsigned char pad510[0xF80 - 0x510];
    int xF80;  // 0xF80
    unsigned char padF84[0x1010 - 0xF84];
    int x1010;  // 0x1010
    unsigned char pad1014[0x1020 - 0x1014];
    float x1020;  // 0x1020
    unsigned char pad1024[0x10A0 - 0x1024];
    int x10A0;  // 0x10A0
    unsigned char pad10A4[0x10D4 - 0x10A4];
    int x10D4;  // 0x10D4
    unsigned char pad10D8[0x1108 - 0x10D8];
    Obj * x1108;  // 0x1108
    unsigned char pad110C[0x1140 - 0x110C];
    void * x1140;  // 0x1140
    unsigned char pad1144[0x1294 - 0x1144];
    int x1294;  // 0x1294
    unsigned char pad1298[0x13C8 - 0x1298];
    int x13C8;  // 0x13C8
    unsigned char pad13CC[0x1520 - 0x13CC];
    int x1520;  // 0x1520
    unsigned char pad1524[0x18E4 - 0x1524];
    int x18E4;  // 0x18E4
    unsigned char pad18E8[0x19B8 - 0x18E8];
    Obj * x19B8;  // 0x19B8
    unsigned char pad19BC[0x19D0 - 0x19BC];
    qword x19D0;  // 0x19D0
    unsigned char pad19E0[0x1A00 - 0x19E0];
    qword x1A00;  // 0x1A00
};
union Slot { int i; unsigned u; float f; Node *node; int *list; Slot *sub; };
struct Node {
    unsigned type : 8;
    unsigned pad01 : 24;
    int pad04;
    Slot a;
    Slot b;
};
extern "C" {
extern int D_0046FD00, D_0046FC30, D_00474FF0, D_00475480, D_0036E740, D_00479D5C, D_004BC228;
extern float D_00326830, D_00344838;
Obj *func_00226348(Env *env, Node *condition, Ctx *ctx);
void func_001D2770(Arena *arena);
void func_001D2798(Arena *arena, int mode);
void *func_001D25B0(Request *request);
int func_00226270(Env *env, int id);
void func_002261F0(Env *env, int id);
int func_001566D0(void *p);
int func_00138AC8(void *p);
int func_00239CC0(void *p);
void func_0022B718(Ctx *ctx);
int func_00260738(void *p);
void func_0022B770(Ctx *ctx);
int func_0021DD30(void *p);
float func_00226458(Env *env);
void func_0022A430(float elapsed, Ctx *ctx, Node *node);
void func_001BF128(void *source, void *destination);
float func_0011EE68(void *table, float value);
int func_0013B500(void *object, int kind);
Obj *func_00226770(Ctx *ctx, int id);
void func_0022AEC8(Ctx *ctx, Obj *target, void *out, int flag);
void func_001572A0(void *p, qword position);
void func_00156690(void *p);
void *func_002387A8(void *list, int id);
int func_001577C0(void *p);
int func_00157950(void *p);
void func_00238568(void *list);
int func_00154DA0(void *p);
int func_00154ED0(void *p);
int func_00154EE0(void *p);
int func_00154F40(void *p);
Obj *func_00226B78(Ctx *ctx);
Obj *func_00226BB0(Ctx *ctx);
int func_0016AEF8(void *p);
int func_0016AFB8(void *p);
void func_0016B078(void *p);
int func_00226578(Ctx *ctx);
void func_0022BEE8(Ctx *ctx);
Node *func_0022A500(Ctx *ctx, Node *node);
void func_0022BB78(Ctx *ctx, Node *a, Node *b, Node *c);
void *func_0017E1B8(void *world, int kind, int id, int flag);
int func_001A7A80(void *target, int id, float zero);
int func_00239E70(void *p);
int func_001F4AD0(void *world, int index);
void func_0022B670(Ctx *ctx);
int func_00248858(void *p, int id);
float func_002483D8(void *p);
int func_001985F0(void *a, void *b);
int func_0011E9F0(float a, float b, float epsilon);
void func_0022B7B8(Ctx *ctx);
int func_00163700();
void func_001636B0(void *p);
int func_00163738(void *p);
void *func_0011E118(void *pool);
void func_0011AF60(void *list, void *entry);
void func_0022BF08(Ctx *ctx, Node *node, int type);
}
union U { qword q; float f[4]; };
struct Pair { Node *first; Node *second; };
#define VCALL(o, slot, T) ((T)((o)->vt[slot].fn))
#define SELF(o, slot) ((char *)(o) + (o)->vt[slot].delta)
static __inline__ qword Position(Obj *o)
{
    return ((qword *(*)(void *))(o->vt[36].fn))(SELF(o, 36))[3];
}
static __inline__ qword Distance2D(qword a, qword b)
{
    qword d, f;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__ __volatile__("vmul.xy %0,%0,%0
	vaddy.x %0,%0,%0y" : "=j"(f) : "0"(d));
    return f;
}
static __inline__ qword SqrtX(qword d)
{
    qword l;
    __asm__ __volatile__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static __inline__ float ToFloat(qword q) { float f; __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(q)); return f; }
static __inline__ float LaneX(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static __inline__ float LaneY(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
static __inline__ float LaneZ(qword q) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(q)); return f; }
/* Script condition evaluator: returns whether the condition `node` holds, switching on the node type (12..116). */
extern "C" int func_00229438(Ctx *context, Node *node)
{
    register Ctx *ctx asm("$17") = context; /* register pin */
    int ok;
    int scanId, scanIndex;
    Arena arena;
    /* Scratch pointers shared by several cases (one C variable each): they hold the tested object / actor,
       which also fixes the registers the allocator gives to the tested pointers. */
    Obj *pa;
    Obj *po;
    switch (node->type) {
    case 12: {
        int i;
        ok = 1;
        for (i = 0; i < node->a.i; i++) {
            if (func_00226348(ctx->env, node->b.sub[i].node, ctx)) {
                ok = 0;
                break;
            }
        }
        break;
    }
    case 13: {
        Request request;
        int found, i;
        Obj **matched;
        if (ctx->x108) {
            ctx->x108 = 0;
            ok = 1;
            break;
        }
        func_001D2770(&arena);
        found = 0;
        Request *r = &request;
        r->size = node->a.sub[0].i * 4;
        r->alignment = 16;
        matched = (Obj **)func_001D25B0(r);
        for (i = 0; i < node->a.sub[0].i; i++) {
            Obj *candidate;
            int id = node->a.sub[1].list[i];
            if (id == ctx->x2C->x4)
                continue;
            candidate = func_00226348(ctx->env, (Node *)id, ctx);
            if (!candidate)
                goto scanned;
            if (!candidate->x34)
                goto scanned;
            if (candidate->x34->type != 0xD)
                goto scanned;
            if (candidate->x34->a.sub[2].i != node->a.sub[2].i)
                goto scanned;
            if (candidate->x108)
                goto scanned;
            matched[found++] = candidate;
        }
    scanned:
        if (found == node->a.sub[0].i - 1) {
            int k;
            for (k = 0; k < found; k++)
                matched[k]->x108 = 1;
            ok = 1;
        } else {
            ok = 0;
        }
        func_001D2798(&arena, 2);
        break;
    }
    case 14:
        ok = func_00226270(ctx->env, node->a.i);
        if (ok && node->b.i)
            func_002261F0(ctx->env, node->a.i);
        break;
    case 22:
        ok = 0;
        if (ctx->x5C) {
            if (func_001566D0(ctx->x5C))
                break;
            ctx->x5C = 0;
            ok = 1;
            break;
        }
        if (ctx->x54 && func_00138AC8(ctx->x54)) {
            VCALL(ctx->x54, 2, void (*)(void *))(SELF(ctx->x54, 2));
            ctx->x54 = 0;
        }
        ok = ctx->x54 == 0;
        break;
    case 23:
        if (ctx->x58 && !ctx->x58->flags60.first)
            ctx->x58 = 0;
        ok = ctx->x58 == 0;
        break;
    case 25:
        if (ctx->x60 && (func_00239CC0(ctx->x60) || ctx->x64))
            func_0022B718(ctx);
        ok = ctx->x60 == 0;
        break;
    case 26:
        if (ctx->x6C && func_00260738(ctx->x6C))
            func_0022B770(ctx);
        ok = ctx->x6C == 0;
        break;
    case 28:
        ok = !func_0021DD30(&D_0046FD00);
        break;
    case 29: {
        float elapsed;
        ok = 1;
        elapsed = func_00226458(ctx->env) - ctx->stamp;
        func_0022A430(elapsed, ctx, node);
        ok = node->a.sub[6].f <= func_00226458(ctx->env) - ctx->stamp;
        break;
    }
    case 38: {
        float table[4];
        float *out;
        if (!ctx->obj) {
            ok = 1;
            break;
        }
        out = table;
        func_001BF128(&ctx->obj->x1010, out);
        {
            float v = func_0011EE68(out, ctx->x84);
            float d = ctx->obj->x1020 - v;
            ok = (d < 0 ? -d : d) < node->b.f;
        }
        break;
    }
    case 39:
        pa = ctx->actor;
        if (!pa) {
            ok = 1;
            break;
        }
        if (!func_0013B500(pa, 0x33)) {
            ok = 1;
            break;
        }
        {
            Obj *actor = ctx->actor;
            if ((unsigned)(actor->x33C - 0xC) < 3)
                ok = 0;
            else if (actor->x50C == -1)
                ok = 1;
            else if (actor->x508 == 0 || actor->x508 == 0xD) {
                VCALL(actor, 99, void (*)(void *, int))(SELF(actor, 99), 0);
                ok = 1;
            } else
                ok = 1;
        }
        break;
    case 40:
        pa = ctx->actor;
        if (!pa) {
            ok = 1;
            break;
        }
        if (!func_0013B500(pa, 0x33)) {
            ok = 1;
            break;
        }
        ok = ctx->actor->x10D4 == -1;
        break;
    case 41:
    case 45:
        po = ctx->obj;
        if (!po) {
            ok = 1;
            break;
        }
        ok = func_00154DA0(po);
        break;
    case 42:
        po = ctx->obj;
        if (!po) {
            ok = 1;
            break;
        }
        ok = func_00154ED0(po);
        break;
    case 43:
        po = ctx->obj;
        if (!po) {
            ok = 1;
            break;
        }
        ok = func_00154EE0(po);
        break;
    case 46:
        po = ctx->obj;
        if (!po) {
            ok = 1;
            break;
        }
        ok = func_00154F40(po);
        break;
    case 47:
        ok = 1;
        ok = ctx->x168 < func_00226458(ctx->env) - ctx->stamp;
        break;
    case 48: {
        Obj *obj = ctx->obj;
        Obj *target;
        U out;
        if (!obj) {
            ok = 1;
            break;
        }
        target = func_00226770(ctx, node->a.sub[0].i);
        if (target) {
            func_0022AEC8(ctx, target, &out, 0);
            ok = 1;
            {
                qword pos = Position(obj);
                Slot *args = node->a.sub;
                qword dist = SqrtX(Distance2D(pos, out.q));
                float lim = args[2].f;
                ok = ToFloat(dist) < lim;
            }
            func_001572A0(&obj->x10A0, out.q);
        } else {
            ok = 1;
        }
        if (!ok)
            break;
        func_00156690(obj);
        ctx->x5C = 0;
        break;
    }
    case 51: {
        Obj *actor;
        void *list;
        void *item;
        pa = ctx->actor;
        if (!pa) {
            ok = 1;
            break;
        }
        if (!func_0013B500(pa, 0x33)) {
            ok = 1;
            break;
        }
        actor = ctx->actor;
        ok = 0;
        list = &actor->x29C;
        item = func_002387A8(list, 0xF3);
        if (!item || func_001577C0(item))
            ok = 1;
        if (!ok)
            break;
        if (item) {
            func_00238568(list);
            func_00156690(actor);
        }
        ctx->x5C = 0;
        break;
    }
    case 52: {
        Obj *actor;
        void *list;
        void *item;
        pa = ctx->actor;
        if (!pa) {
            ok = 1;
            break;
        }
        if (!func_0013B500(pa, 0x33)) {
            ok = 1;
            break;
        }
        actor = ctx->actor;
        ok = 0;
        list = &actor->x29C;
        item = func_002387A8(list, 0xF4);
        if (!item || func_00157950(item))
            ok = 1;
        if (!ok)
            break;
        if (item) {
            func_00238568(list);
            func_00156690(actor);
        }
        ctx->x5C = 0;
        break;
    }
    case 53: {
        Obj *obj = ctx->obj;
        Obj *target;
        U out;
        if (!obj) {
            ok = 1;
            break;
        }
        if (obj->x50C == -1) {
            ok = 1;
            break;
        }
        if (obj->x508 != 8) {
            ok = 1;
            break;
        }
        target = func_00226770(ctx, node->a.sub[0].i);
        if (!target) {
            ok = 1;
            break;
        }
        func_0022AEC8(ctx, target, &out, 0);
        ok = 1;
        {
            qword pos = Position(obj);
            Slot *args = node->a.sub;
            qword dist = SqrtX(Distance2D(pos, out.q));
            float lim = args[2].f;
            ok = ToFloat(dist) < lim;
        }
        break;
    }
    case 54:
        po = ctx->obj;
        if (!po) {
            ok = 1;
            break;
        }
        ok = po->x33C == -1;
        break;
    case 55:
        pa = ctx->actor;
        if (!pa) {
            ok = 1;
            break;
        }
        if (!func_0013B500(pa, 0x33)) {
            ok = 1;
            break;
        }
        ok = ctx->actor->x33C == -1;
        break;
    case 56:
    case 57:
        if (ctx->x68) {
            if (node->type == 0x38) {
                if ((int)(ctx->x68->flags >> 56) & 1) {
                    if (ctx->x68->x104 == 1.0f)
                        ctx->x68 = 0;
                }
            } else if (((int)(ctx->x68->flags >> 56) & 1) == 0) {
                ctx->x68 = 0;
            }
        }
        ok = ctx->x68 == 0;
        break;
    case 63:
        ok = 1;
        ok = D_00344838 < func_00226458(ctx->env) - ctx->stamp;
        break;
    case 64:
        ok = 1;
        ok = node->a.f < func_00226458(ctx->env) - ctx->stamp;
        break;
    case 69: {
        Node *chain[3];
        int saved;
        {
            int busy = func_00226578(ctx);
            ok = 0;
            if (busy)
                break;
        }
        ctx->x88 = D_00326830;
        ok = 1;
        if (node->a.sub[11].u & 0x60) {
            func_0022BEE8(ctx);
            break;
        }
        chain[0] = node;
        chain[1] = 0;
        chain[2] = 0;
        saved = ctx->x1C;
        chain[1] = func_0022A500(ctx, node);
        if (chain[1]) {
            chain[2] = func_0022A500(ctx, chain[1]);
            if (!chain[2])
                chain[2] = chain[1];
        } else {
            chain[2] = chain[0];
            chain[1] = chain[0];
        }
        ctx->x1C = saved;
        func_0022BB78(ctx, chain[0], chain[1], chain[2]);
        break;
    }
    case 70: {
        Obj *o;
        o = func_00226B78(ctx);
        if (o)
            ok = o->xF80 == 1;
        else
            ok = 1;
        break;
    }
    case 71: {
        Obj *o;
        o = func_00226B78(ctx);
        if (!o) {
            ok = 1;
            break;
        }
        ok = o->xF80 == -1;
        break;
    }
    case 72: {
        Obj *o;
        o = func_00226BB0(ctx);
        if (!o) {
            ok = 1;
            break;
        }
        ok = func_0016AEF8(o);
        break;
    }
    case 73: {
        Obj *o;
        o = func_00226BB0(ctx);
        if (!o) {
            ok = 1;
            break;
        }
        ok = func_0016AFB8(o);
        break;
    }
    case 75: {
        Obj *o;
        o = func_00226BB0(ctx);
        if (!o) {
            ok = 1;
            break;
        }
        func_0016B078(o);
        break;
    }
    case 77: {
        Obj *o;
        o = func_00226B78(ctx);
        if (o)
            ok = o->xF80 == 1;
        else
            ok = 1;
        break;
    }
    case 78: {
        void *target = &D_0036E740;
        if (node->b.i != -1) {
            void *o = func_0017E1B8(&D_00475480, 5, node->b.i, 0);
            if (o) {
                if (func_0013B500(o, 0x31)) {
                    void *replacement = *(void **)((char *)o + 0x134);
                    if (replacement)
                        target = replacement;
                }
            }
        }
        ok = func_001A7A80(target, node->a.i, 0.0f) != 0;
        if (ok)
            D_004BC228 = 0;
        break;
    }
    case 79:
        pa = ctx->actor;
        if (!pa) {
            ok = 1;
            break;
        }
        if (!func_0013B500(pa, 0x33)) {
            ok = 1;
            break;
        }
        ok = VCALL(ctx->actor, 100, int (*)(void *))(SELF(ctx->actor, 100)) == node->a.i;
        goto done;
    case 80:
        ok = !func_0021DD30(&D_0046FC30);
        break;
    case 81: {
        Obj *o;
        int i;
        ok = 1;
        if (node->a.i == -1)
            break;
        o = func_00226770(ctx, node->a.i);
        if (!o)
            break;
        if (!func_0013B500(o, 0x31))
            break;
        for (i = 0; i < 2; i++) {
            if ((int)o == func_001F4AD0(&D_00475480, i)) {
                ok = 0;
                break;
            }
        }
        break;
    }
    case 82:
        func_0022B670(ctx);
        ok = !func_00248858(&D_00474FF0, node->a.sub[7].i);
        break;
    case 95:
        func_0022B670(ctx);
        ok = !func_00248858(&D_00474FF0, -1);
        break;
    case 88:
        ok = 1;
        ok = node->a.f <= func_002483D8(&D_00474FF0);
        break;
    case 91:
        ok = 1;
        ok = node->a.f <= func_002483D8(&D_00474FF0);
        break;
    case 92:
        ok = 0;
        if (!func_0013B500(ctx->actor, 0x35))
            break;
        if (ctx->actor->x1520 != 6) {
            ok = 1;
            break;
        }
        if (node->a.sub[2].i == -1)
            break;
        ok = func_00239E70(ctx->actor->x1140) == node->a.sub[2].i;
        break;
    case 93:
        ok = 0;
        po = ctx->obj;
        if (!po)
            goto yes93;
        if (po->x1520 != 8)
            break;
    yes93:
        ok = 1;
        break;
    case 94:
        ok = 0;
        po = ctx->obj;
        if (!po)
            goto yes94;
        if (po->x1520 == 8)
            break;
    yes94:
        ok = 1;
        break;
    case 96:
        ok = 1;
        ok = node->b.f < func_00226458(ctx->env) - ctx->stamp;
        break;
    case 98:
        if (ctx->x100 && !func_001985F0(ctx->xFC, ctx->x100)) {
            ctx->xFC = 0;
            ctx->x100 = 0;
        }
        ok = ctx->x100 == 0;
        break;
    case 101: {
        Obj *o;
        if (!ctx->obj) {
            ok = 1;
            break;
        }
        o = func_00226770(ctx, node->a.i);
        if (func_00226458(ctx->env) - ctx->stamp > 7.0f) {
            ok = 1;
            break;
        }
        {
            int state = o->x18E4;
            ok = 0;
            if (state >= 7)
                break;
            ok = state >= 4;
        }
        break;
    }
    case 102: {
        qword first, second;
        if (!ctx->obj) {
            ok = 1;
            break;
        }
        if (func_00226458(ctx->env) - ctx->stamp > 10.0f) {
            ok = 1;
            break;
        }
        first = ctx->obj->x1A00;
        second = ctx->obj->x19D0;
        ok = 0;
        if (!func_0011E9F0(LaneX(first), LaneX(second), 0.1f))
            break;
        if (!func_0011E9F0(LaneY(first), LaneY(second), 0.1f))
            break;
        ok = func_0011E9F0(LaneZ(first), LaneZ(second), 0.1f) != 0;
        break;
    }
    case 103: {
        int state;
        if (!ctx->obj) {
            ok = 1;
            break;
        }
        if (func_00226458(ctx->env) - ctx->stamp > 10.0f) {
            ok = 1;
            break;
        }
        state = ctx->obj->x18E4;
        ok = 0;
        if ((unsigned)(state + 1) >= 2)
            break;
        if (state == 0)
            VCALL(ctx->obj, 99, void (*)(void *, int))(SELF(ctx->obj, 99), 0);
        ok = ctx->x94->x33C == -1;
        break;
    }
    case 106:
        pa = ctx->actor;
        if (!pa) {
            ok = 1;
            break;
        }
        ok = pa->x1108->x48 == -1;
        break;
    case 108:
        if (!ctx->x16C) {
            ok = 1;
            break;
        }
        ok = 0;
        scanId = ctx->x16C->x198;
        if (ctx->x16C->x190 == 1)
            break;
        if (scanId != -1) {
            for (scanIndex = 0; scanIndex < node->a.sub[1].i; scanIndex++) {
                if (scanId == node->a.sub[2].list[scanIndex])
                    goto found;
            }
            break;
        }
        func_0022B7B8(ctx);
        ok = 1;
        break;
    case 115:
        po = ctx->x16C;
        if (!po) {
            ok = 1;
            break;
        }
        ok = 0;
        if (po->x190 == 1)
            break;
        if ((node->a.i & 1) == 0) {
            ok = 1;
            break;
        }
        if (func_00163700())
            func_001636B0(ctx->x16C);
        if (!func_00163738(ctx->x16C))
            break;
        func_0022B7B8(ctx);
        ok = 1;
        break;
    case 116: {
        Obj *actor;
        if (!ctx->actor) {
            ok = 1;
            break;
        }
        if (func_00226458(ctx->env) - ctx->stamp > 10.0f) {
            ok = 1;
            break;
        }
        actor = ctx->actor;
        if (actor->x1294 == 4 || actor->x1294 == 6 || actor->x1294 == 5) {
            ok = 0;
            if (actor->x13C8)
                break;
        } else {
            Obj *o;
            void *p;
            o = actor->x19B8;
            if (!o) {
                ok = 0;
                break;
            }
            p = o->x2DC;
            if (p) {
                ok = 0;
                if (func_00239E70(p) == 0x92 || func_00239E70(p) == 0xA8)
                    ok = 1;
            } else
                ok = 1;
            if (!ok)
                break;
            if (!node->b.i)
                break;
        }
        VCALL(actor, 114, void (*)(void *, int))(SELF(actor, 114), 0xD);
        break;
    }
    found: {
        Pair *entry;
        func_0022B7B8(ctx);
        ok = 1;
        entry = (Pair *)func_0011E118(&D_00479D5C);
        entry->first = (Node *)scanId;
        entry->second = node;
        func_0011AF60(&ctx->x15C, entry);
        func_0022BF08(ctx, (Node *)node->a.sub[3].list[scanIndex], node->type);
        break;
    }
    case 104:
        ok = 0;
        break;
    default:
        ok = 1;
        break;
    }
    return ok;
done: /* case 79 returns through its own copy of the epilogue (keeps its compare tail from being merged with case 92's) */
    return ok;
}
