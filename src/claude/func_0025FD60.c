// SLY3_CFLAGS: -Os -G0
// Sly3: build the static full-screen strip GIF packet (D_004BADC0) and the clear packet (cf src/claude/func_001837E0.c).
typedef unsigned long u_long;
struct RES { int w; int h; int flags; };
struct GS { int pad0; struct RES res; };
struct GIFS { int a[12]; };
struct QW { int a[4]; } __attribute__((aligned(16)));
struct RECT { int x, y, w, h; };
extern struct GS D_0036DBE0;
extern u_long D_0036DC20;
extern struct QW D_004BADC0[];
extern struct QW D_004BAD80[];
extern int D_004BADB0;
extern char D_004BB1F0[];
void *memset(void *, int, unsigned int);
void func_0018C750(struct GIFS *pg);
void AllocStatic__4DMASiP2QW(struct GIFS *pg, int n, struct QW *pqw);
void AddPrimPack__4GIFSiiUl(struct GIFS *pg, int prim, int nreg, u_long regs);
void PackAD__4GIFSll(struct GIFS *pg, long reg, long val);
void AddPrimEnd__4GIFS(struct GIFS *pg);
void Detach__4DMASPiPP2QW(struct GIFS *pg, int *pc, void *pp);
int func_002BC640(struct GS *p, int w);
int func_002BC648(struct GS *p, int h);
int func_002BC668(struct GS *p, int x);
int func_002BC670(struct GS *p, int y);
void func_0025FBF8(struct RECT *r, int n, void *p);
static inline void SetSize(struct RECT *p, int w, int h) { p->w = w; p->h = h; }
#define g (&D_0036DBE0)
void func_0025FD60(void)
{
    struct GIFS gifs;
    struct GIFS gifs2;
    struct RECT r;
    int x;
    memset(D_004BADC0, 0, 0x2F0);
    D_004BADB0 = 0;
    func_0018C750(&gifs);
    AllocStatic__4DMASiP2QW(&gifs, 0x2F, D_004BADC0);
    AddPrimPack__4GIFSiiUl(&gifs, 0x46, 1, 0xE);
    PackAD__4GIFSll(&gifs, 0x4A, 1);
    PackAD__4GIFSll(&gifs, 0x42, 0x4A);
    PackAD__4GIFSll(&gifs, 0x47, 0x31001);
    for (x = 0; x < func_002BC640(g, g->res.w); x += 32) {
        int c = 0x800;
        int x1 = x + 32;
        int X2;
        int X = func_002BC668(g, x + (c - func_002BC640(g, g->res.w) / 2));
        PackAD__4GIFSll(&gifs, 5, X | ((u_long)func_002BC670(g, c - func_002BC648(g, g->res.h) / 2) << 16));
        X2 = func_002BC668(g, x1 + (c - func_002BC640(g, g->res.w) / 2));
        PackAD__4GIFSll(&gifs, 5, X2 | ((u_long)func_002BC670(g, func_002BC648(g, g->res.h) + (c - func_002BC648(g, g->res.h) / 2)) << 16));
    }
    PackAD__4GIFSll(&gifs, 0x4A, 0);
    PackAD__4GIFSll(&gifs, 0x42, 0x44);
    PackAD__4GIFSll(&gifs, 0x47, 0x50000);
    AddPrimEnd__4GIFS(&gifs);
    Detach__4DMASPiPP2QW(&gifs, &D_004BADB0, 0);
    func_0018C750(&gifs2);
    {
        u_long v = D_0036DC20;
        AllocStatic__4DMASiP2QW(&gifs2, 3, D_004BAD80);
        AddPrimPack__4GIFSiiUl(&gifs2, 0, 1, 0xE);
        PackAD__4GIFSll(&gifs2, 0x3F, 0);
        PackAD__4GIFSll(&gifs2, 0x4E, (v & 0x1FF) | 0x3A000000);
    }
    AddPrimEnd__4GIFS(&gifs2);
    r.x = 0;
    r.y = 0;
    SetSize(&r, 0x280, 0x1E0);
    func_0025FBF8(&r, 2, D_004BB1F0);
}
