// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3 DMA packet builder (cf Sly2 func_002163B0 second half): GIF direct chunks + E record.
typedef unsigned int uint;
typedef unsigned long ulong;
struct R { char pad[0xC]; unsigned char *cur; };
struct E { int kind; float priority; uint address; int tag; };
extern "C" {
extern struct R D_0036C308;
extern char D_004BAD80[], D_004BB1D0[], D_0036DF90[];
extern int D_0036DF80;
void CopyAqw__FPvT0i(void *, void *, int);
struct E *func_00209B60(void);
void func_002618C8(int n, float priority, void *src);
}
static inline void Word(struct R *r, uint word) { *(uint *)r->cur = word; r->cur += 4; }
static inline void Align(struct R *r, int word) { while (((uint)r->cur & 15) != 4 * word) Word(r, 0); }
static inline void Bulk(struct R *r, int n, void *source) { CopyAqw__FPvT0i(r->cur, source, n); r->cur += n * 16; }
static inline void Direct(struct R *r, int n, void *source) { Align(r, 3); Word(r, 0x50000000 | n); Bulk(r, n, source); }

void func_002618C8(int n, float priority, void *src)
{
    unsigned char *tag;
    struct E *e;
    tag = D_0036C308.cur;
    *(ulong *)tag = 0x10000000UL; D_0036C308.cur += 16;
    Word(&D_0036C308, 0x11000000);
    Direct(&D_0036C308, 3, D_004BAD80);
    Direct(&D_0036C308, D_0036DF80, D_0036DF90);
    Direct(&D_0036C308, 2, D_004BB1D0);
    if (src) Direct(&D_0036C308, n, src);
    Word(&D_0036C308, 0x11000000);
    Align(&D_0036C308, 0);
    *(uint *)tag |= ((D_0036C308.cur - tag) >> 4) - 1;
    *(ulong *)D_0036C308.cur = 0x60000000UL; D_0036C308.cur += 16;
    e = func_00209B60();
    e->kind = 0x90; e->priority = priority * 65536.0f;
    e->address = (uint)tag & 0x0FFFFFFF; e->tag = 0;
}
