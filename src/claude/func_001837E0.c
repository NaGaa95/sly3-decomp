// SLY3_CFLAGS: -Os -G0
// New Sly 3 code: draws the previous frame buffer back as 32-pixel-wide sprite strips through a GIFS packet.
// The 0x800 origin lives in a local so combine does not reassociate the offsets; D_0036DBE0 is used directly.
// .rodata of the original unit at 0x321868/0x321878 (u/v offset tables) is defined below.
typedef unsigned long u_long;
struct RES { int w; int h; int flags; };
struct FRAME { u_long fbp : 9; u_long p0 : 7; u_long fbw : 6; u_long p1 : 2; u_long psm : 6; u_long p2 : 2; u_long fbmsk : 32; };
struct GS { int pad0; struct RES res; int pad10[8]; struct FRAME frame[2]; };
struct GIFS { int a[12]; };
struct QW { int a[4]; } __attribute__((aligned(16)));
extern int D_0036C6D4;
extern struct GS D_0036DBE0;
extern int D_0036DC90, D_0036DC98;
extern int D_0036DCA0[2];
extern int D_0036BD40;
static const int D_00321868[4] = { 8, 16, 16, 8 };
static const int D_00321878[4] = { 0, 16, 0, 0 };
void func_0018C750(struct GIFS *pg);
void AllocStatic__4DMASiP2QW(struct GIFS *pg, int n, struct QW *pqw);
void AddDmaCnt__4DMAS(struct GIFS *pg);
void AddPrimPack__4GIFSiiUl(struct GIFS *pg, int prim, int nreg, u_long regs);
void PackAD__4GIFSll(struct GIFS *pg, long reg, long val);
void PackUV__4GIFSii(struct GIFS *pg, int u, int v);
void PackXYZF__4GIFSiiii(struct GIFS *pg, int x, int y, int z, int f);
void AddPrimEnd__4GIFS(struct GIFS *pg);
void AddDmaEnd__4DMAS(struct GIFS *pg);
void EndDmaCnt__4DMAS(struct GIFS *pg);
void func_00195760(int n, struct QW *pqw);
int func_002BC640(struct GS *p, int w);
int func_002BC648(struct GS *p, int h);
int func_002BC668(struct GS *p, int x);
int func_002BC670(struct GS *p, int y);
#define g (&D_0036DBE0)
void func_001837E0(void)
{
    struct GIFS gifs;
    struct QW aqw[0x64];
    struct FRAME *pf;
    int x, du, dv;
    if (D_0036C6D4)
        return;
    if ((g->res.flags >> 1) & 1)
        return;
    func_0018C750(&gifs);
    AllocStatic__4DMASiP2QW(&gifs, 0x64, aqw);
    AddDmaCnt__4DMAS(&gifs);
    AddPrimPack__4GIFSiiUl(&gifs, 0, 1, 0xE);
    PackAD__4GIFSll(&gifs, 0x3F, 0);
    pf = &g->frame[1 - D_0036DC90];
    {
        int fbp = pf->fbp;
        PackAD__4GIFSll(&gifs, 6, ((u_long)fbp << 5) | ((u_long)pf->fbw << 14) | ((u_long)pf->psm << 20) | ((u_long)10 << 26) | ((u_long)10 << 30));
    }
    PackAD__4GIFSll(&gifs, 0x14, 0x61);
    PackAD__4GIFSll(&gifs, 8, 5);
    PackAD__4GIFSll(&gifs, 0x47, 0x33001);
    PackAD__4GIFSll(&gifs, 0x42, ((u_long)0x30 << 32) | 0x64);
    PackAD__4GIFSll(&gifs, 1, 0x3F80000080808080);
    {
        int w = func_002BC640(g, g->res.w);
        PackAD__4GIFSll(&gifs, 0x40, ((u_long)(w - 1) << 16) | ((u_long)1 << 32) | ((u_long)(func_002BC648(g, g->res.h) - 2) << 48));
    }
    AddPrimPack__4GIFSiiUl(&gifs, 0x156, 2, 0x43);
    {
        int off = D_0036DCA0[1 - D_0036DC90] == 1 ? 4 : 0;
        int off2 = D_0036DC98 == 1 ? off + 8 : off;
        du = *(const int *)((const char *)D_00321868 + off2);
        dv = *(const int *)((const char *)D_00321878 + off2);
    }
    for (x = 0; x < func_002BC640(g, g->res.w); x += 32) {
        int x1;
        int c = 0x800;
        PackUV__4GIFSii(&gifs, (x << 4) | 8, du);
        x1 = x + 32;
        {
            int X = func_002BC668(g, x + (c - func_002BC640(g, g->res.w) / 2));
            PackXYZF__4GIFSiiii(&gifs, X, func_002BC670(g, c - func_002BC648(g, g->res.h) / 2) + dv, 0, 0);
        }
        PackUV__4GIFSii(&gifs, (x1 << 4) + 8, (func_002BC648(g, g->res.h) << 4) + du);
        {
            int X = func_002BC668(g, x1 + (c - func_002BC640(g, g->res.w) / 2));
            int h = func_002BC648(g, g->res.h);
            PackXYZF__4GIFSiiii(&gifs, X, func_002BC670(g, h + (c - func_002BC648(g, g->res.h) / 2)) + dv, 0, 0);
        }
    }
    AddPrimPack__4GIFSiiUl(&gifs, 0, 1, 0xE);
    {
        int w = func_002BC640(g, g->res.w);
        PackAD__4GIFSll(&gifs, 0x40, ((u_long)(w - 1) << 16) | ((u_long)(func_002BC648(g, g->res.h) - 1) << 48));
    }
    PackAD__4GIFSll(&gifs, 0x61, 0);
    AddPrimEnd__4GIFS(&gifs);
    AddDmaEnd__4DMAS(&gifs);
    EndDmaCnt__4DMAS(&gifs);
    func_00195760(D_0036BD40, aqw);
}
