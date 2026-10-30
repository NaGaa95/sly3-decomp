// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *, ...); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct REQ { int cb; int align; };
struct ENT { struct Object *o; int x; };
struct T { float m[16]; char pad[0x94 - 0x40]; int x94; char pad2[0xA4 - 0x98]; int xA4; };
struct G { char pad[0x44F4]; int count; };
struct PAIR { int a; int b; };
struct S { unsigned char pad00[0xC]; struct Method *methods; char pad[0x44 - 0x10]; struct T *x44;
           char pad2[0x1160 - 0x48]; int x1160; int pad1164; struct ENT *ents; int n; };
extern char D_00342DC0[];
extern struct G D_00475480;
extern char D_0036C700[];
extern int D_0036DBEC;
void func_0024D9D8(void *s);
void func_001C8970(void *s, int a, void *b, int c);
void func_001B71D8(void *p);
void func_001B2720(void *p);
void func_001C2058(void *p);
void func_001BDA68(void *p);
void func_00271EE8(void *p);
void func_001BEE70(void *p);
void func_00139B98(void *p);
int func_0017DE98(void *g, int a, int b, void *s, int max, struct Object **out);
void *func_001D2538(struct REQ *r);
void func_001F4670(void *s, int n);
int func_00241AD8(void *s);
struct PAIR *func_00185720(void *g, void *s);
void func_001F43D0(void *s, int n);
void func_001F4438(void *s, int n);
void func_00292034(void *p, int c, int n);
int func_0023FDE8(void *s, int n);
void func_0023FE38(void *s, int n);
void func_0023FEC0(void *s, int n);
#define MATRIX(o) ((struct Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static inline void LoadIdentity(struct T *t)
{
    func_00292034(t, 0, 0x40);
    t->m[15] = 1.0f;
    t->m[10] = 1.0f;
    t->m[5] = 1.0f;
    t->m[0] = 1.0f;
}
static inline void *Alloc(int cb)
{
    struct REQ r;
    r.cb = cb;
    r.align = 16;
    return func_001D2538(&r);
}
void func_00152488(struct S *s)
{
    struct Object *buf[16];
    int n;
    int i;
    struct PAIR *e;
    char *p = (char *)s;
    func_0024D9D8(s);
    func_001C8970(s, 0x3B, D_00342DC0 + 0x10, 0);
    func_001B71D8(p + 0x320);
    func_001B2720(p + 0x500);
    func_001C2058(p + 0xE40);
    func_001BDA68(p + 0xF60);
    func_00271EE8(p + 0x1290);
    func_001BEE70(p + 0x1010);
    func_00139B98(p + 0x10D0);
    n = func_0017DE98(&D_00475480, 0x401, 0x301, s, 16, buf);
    if (n) {
        s->n = n;
        s->ents = Alloc(n * 8);
        for (i = 0; i < n; i++) {
            struct Object *o;
            s->ents[i].o = buf[i];
            o = s->ents[i].o;
            o->methods[9].call((unsigned char *)o + o->methods[9].delta);
        }
    }
    func_001F4670(s, 1);
    s->x1160 = func_00241AD8(s);
    e = func_00185720(D_0036C700, s);
    func_001F43D0(s, e->a);
    func_001F4438(s, e->b);
    if (!s->x44->x94) {
        qword pos = MATRIX(s)->rows[3];
        M3 m = *(M3 *)MATRIX(s);
        int c;
        LoadIdentity(s->x44);
        c = ++D_00475480.count;
        s->x44->xA4 = c;
        s->methods[20].call((unsigned char *)s + s->methods[20].delta);
        s->methods[34].call((unsigned char *)s + s->methods[34].delta, pos);
        s->methods[35].call((unsigned char *)s + s->methods[35].delta, &m);
    }
    if (func_0023FDE8(s, 0x306)) {
        if ((D_0036DBEC >> 1) & 1)
            func_0023FE38(s, 0x306);
        else
            func_0023FEC0(s, 0x306);
    }
}
