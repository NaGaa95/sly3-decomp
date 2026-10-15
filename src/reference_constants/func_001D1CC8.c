// Reference algorithm: src/hand/func_001ADA20.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CRef { unsigned short m_tagk,reserved; float m_tag; };
struct E { int x0, x4, x8, xC, x10; int x14; int x18; };
struct G { int pad[14]; int x24; };
struct GD { char pad[0x406C]; int x3B1C; };
struct B { char data[0x6864]; };
extern struct G D_0046F550;
extern struct E D_0046F570[];
extern struct GD D_00475480;
extern struct B D_003752B4[];
int func_001D4658(struct G *g);
int func_001D45B0(struct G *g);
void func_002BC010(struct CRef *ret, int a, void *b);
void func_0012BC20(struct CRef *);
const unsigned short *func_00150630(void *p, int n);
unsigned short *func_00271730(unsigned short *d, const unsigned short *s);
unsigned short *func_00271828(unsigned short *d, const char *s);
unsigned short *func_00271780(unsigned short *d, const unsigned short *s);
void func_001D1CC8(unsigned short *buf)
{
    struct G *g = &D_0046F550;
    struct GD *gd;
    struct CRef ref;
    float f;
    if (!func_001D4658(g))
        return;
    gd = &D_00475480;
    {
    struct E *e = &D_0046F570[g->x24];
    func_002BC010(&ref, gd->x3B1C, &D_003752B4[e->x14]);
    }
    f = ref.m_tag;
    func_0012BC20(&ref);
    switch (func_001D45B0(g)) {
    case 0x2A:
        if (f != 0.0f)
            func_00271730(buf, func_00150630(gd, 0x32));
        else
            func_00271730(buf, func_00150630(gd, 0x33));
        break;
    case 0x2B:
        if (f != 0.0f)
            func_00271730(buf, func_00150630(gd, 0x34));
        else
            func_00271730(buf, func_00150630(gd, 0x33));
        break;
    case 0x25:
        func_00271730(buf, func_00150630(gd, 0x36));
        if (f != 0.0f) {
            func_00271828(buf, "\n");
            func_00271780(buf, func_00150630(gd, 0x32));
        }
        break;
    }
}
