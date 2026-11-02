// SLY3_CFLAGS: -Os -G0 -ffast-math
// Rebuild the visible entry list from the static table (11 entries; some are filtered by game state) and hand it to the
// menu (same routine as Sly 2 func_001B04E0).
struct E { int kind; int a[7]; };
struct G { char pad[0x30]; int x30; };
struct S { char pad[0x1C]; int x1C; };
extern struct E D_00345B40[11], D_00389728[];
extern char D_00375290[], D_0046FC30[], D_00345920[];
extern struct G D_0046F550;
int func_0021DD30(void *p);
int func_001CFDF8(void *p);
void func_001D3818(struct G *g, int n, struct E *pe);
void func_001D3960(struct G *g, int n, struct E *pe, int a, void *b);
void func_001D4C48(struct S *p)
{
    struct E *dst = D_00389728;
    unsigned int i;
    for (i = 0; i < 11; i++) {
        struct E *src = &D_00345B40[i];
        int ok = 1;
        switch (src->kind) {
        case 0xAA:
            ok = func_0021DD30(D_0046FC30);
            break;
        case 0x4B:
            ok = func_0021DD30(D_0046FC30) != 0;
            break;
        case 0x4D:
            ok = 0;
            if (!func_0021DD30(D_0046FC30))
                ok = func_001CFDF8(D_00375290) == 0;
            break;
        case 0x4C:
        case 0x88: case 0x89: case 0x8A: case 0x8B: case 0x8C:
            break;
        }
        if (ok) *dst++ = *src;
    }
    if (p) {
        func_001D3818(&D_0046F550, dst - D_00389728, D_00389728);
        p->x1C |= 2;
    } else {
        func_001D3960(&D_0046F550, dst - D_00389728, D_00389728, D_0046F550.x30, D_00345920);
    }
}
