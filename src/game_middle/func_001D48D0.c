// SLY3_CFLAGS: -Os -G0 -ffast-math
// SLY3_AS: gnu-2.9
// Rebuild the visible main-menu entry list: every entry of the static 11-entry table is kept or dropped by a per-kind
// visibility rule (jump-table switch on the kind), the kept entries are copied to the output array and handed to the
// menu layout (func_001D2D90 / func_001D3960). The entry loop is written with a goto on purpose: a real loop would get
// gcc's loop alignment and invariant hoisting, the target has neither.
struct E { int kind; int a[7]; };
struct VT { short d; short pad; int (*pfn)(void *, int); };
struct Obj { char pad00[0xC]; struct VT *vt; };
struct G { char pad[0x30]; int x30; };
struct Sel { char pad[0x50]; int x50; };
extern struct E D_00345DA0[11], D_00389888[];
extern char D_00345920[];
extern struct G D_0046F550;
extern char D_00475480[];
extern int D_0046FAD4, D_004794CC, D_004794C4, D_0036DBEC;
extern struct Sel *D_004BC244;
int func_0018AE00(void);
void func_001D2D90(struct G *g, int a);
void func_001D3960(struct G *g, int n, struct E *pe, int a, void *b);
struct Obj *func_001F4AD0(void *game, int id);
int func_0025E150(void);
int func_0025E188(void);
int func_00260D10(void);
void func_001D48D0(int id)
{
    if (D_0046F550.x30) {
        struct Obj *o;
        if (id == -1)
            o = 0;
        else
            o = func_001F4AD0(D_00475480, id);
        if (func_00260D10()) {
            struct E *dst = D_00389888;
            unsigned int i = 0;
            struct E *src;
            int ok;
        next:
            {
                src = &D_00345DA0[i];
                ok = 1;
                switch (src->kind) {
                case 0x7A:
                    ok = 0;
                    if (D_0046FAD4)
                        ok = func_0025E150() != 0;
                    break;
                case 0x7E:
                    ok = 0;
                    break;
                case 0x4A:
                    ok = 1;
                    break;
                case 0x53:
                    ok = 0;
                    if (o) {
                        int r = ~o->vt[91].pfn((char *)o + o->vt[91].d, 0xC);
                        ok = r != 0;
                    }
                    break;
                case 0x95:
                    ok = 0;
                    if (D_004794CC && func_0018AE00())
                        ok = ((D_0036DBEC >> 1) & 1) ^ 1;
                    break;
                case 0x96:
                    ok = 0;
                    if (D_004794CC && func_0018AE00())
                        ok = (D_0036DBEC >> 1) & 1;
                    break;
                case 0x7B:
                    ok = 0;
                    if (D_004794C4) {
                        int idx = D_004BC244 ? D_004BC244->x50 : -1;
                        ok = idx == -1 && func_0025E188() != 1 && func_0025E188() != 8 && func_0025E150() != 0x18 &&
                             func_0025E150() != 0x19;
                    }
                    break;
                case 0x52: {
                    int idx = D_004BC244 ? D_004BC244->x50 : -1;
                    switch (idx) {
                    default:
                        break;
                    case 2:
                        ok = 0;
                        break;
                    case 0:
                    case 1:
                        ok = 1;
                        break;
                    case -1:
                        ok = func_0025E188() != 1;
                        break;
                    }
                    ok = ok != 0;
                    break;
                }
                case 0x51: {
                    int idx = D_004BC244 ? D_004BC244->x50 : -1;
                    ok = idx == 2;
                    break;
                }
                }
                if (ok)
                    *dst++ = *src;
            }
            if (++i < 11)
                goto next;
            func_001D2D90(&D_0046F550, id);
            func_001D3960(&D_0046F550, dst - D_00389888, D_00389888, D_0046F550.x30, D_00345920);
        }
    }
}
