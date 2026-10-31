// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_0016FCA8): framebuffer setup packet.
typedef unsigned int uint;
typedef unsigned long ulong;
union QW { ulong aul[2]; uint aun[4]; float ag[4]; } __attribute__((aligned(16)));
enum UPK { UPK_V4_32 = 12 };
class DMAS {
public:
    unsigned char *m_pbMax, *m_ab; QW *m_pqwCnt; unsigned char *m_pb; int m_fPad, m_fEndPrim;
    void AllocStatic(int cqw, QW *aqw);
    void AddDmaCnt();
    void EndDmaCnt();
    void AddDmaRet();
    virtual void EndPrim(int n);
};
class VIFS : public DMAS {
public:
    uint m_unMask;
    VIFS();
    void AddVifFlusha();
    void AddVifDirectRefs(int cqw, QW *aqw, int f);
    void AddVifBaseOffset(int base, int offset);
    void AddVifUnpack(UPK upk, int c, void *pv, int iqw);
};
class GIFS : public DMAS {
public:
    QW *m_pqwPrim; uint m_creg; uint m_cregAll;
    GIFS();
    virtual void EndPrim(int fEOP);
    void AddPrimPack(int prim, int creg, ulong regs);
    void AddPrimEnd();
    void PackAD(long a, long d);
};
typedef unsigned short ushort_t;
union XYOFFSET { ulong word; unsigned short h[4]; };
struct DISPLAY { ulong zbuf; XYOFFSET xyoffset; ulong scissor; };
struct RECT { int x, y, dx, dy; };
struct TEXBITS {
    ulong TBP0 : 14, TBW : 6, PSM : 6, TW : 4, TH : 4, TCC : 1, TFX : 2, CBP : 14, CPSM : 4, CSM : 1, CSA : 5, CLD : 3;
};
union TEX { ulong word; TEXBITS bits; };
extern "C" {
extern int D_0036DC90;
extern ulong D_0036DC10[];
extern DISPLAY D_0036DC20;
void *memset(void *, int, uint);
void func_00195C50(int field, RECT *rect, int gifCount, QW *gifBuffer, int vifCount, QW *vifBuffer, uint mask);
}
void func_00195C50(int field, RECT *rect, int gifCount, QW *gifBuffer, int vifCount, QW *vifBuffer, uint mask)
{
    ulong frame = D_0036DC10[D_0036DC90];
    ulong frame2 = D_0036DC10[1 - D_0036DC90];
    ulong w = D_0036DC10[3];
    XYOFFSET xyoffset;
    xyoffset.word = w;
    if (rect) {
        XYOFFSET *pxy = &xyoffset;
        pxy->word = (w & ~0xFFFFUL) | (ushort_t)((ushort_t)w + (rect->x << 4) / rect->dx);
        pxy->h[2] += (rect->y << 4) / rect->dy;
    } else if (field == 1) {
        XYOFFSET *pxy = &xyoffset;
        pxy->h[2] += 8;
    }
    GIFS gifs;
    gifs.AllocStatic(gifCount, gifBuffer);
    gifs.AddPrimPack(0, 1, 0xEUL);
    ulong fbits = (frame & 0x1FF) | (((frame >> 16) & 0x3F) << 16) | (frame & 0x3F000000) | ((ulong)mask << 32);
    gifs.PackAD(0x4C, fbits);
    gifs.PackAD(0x4E, D_0036DC20.zbuf);
    gifs.PackAD(0x18, xyoffset.word);
    gifs.PackAD(0x40, D_0036DC20.scissor);
    gifs.AddPrimPack(0x200, 1, 0xEUL);
    gifs.PackAD(0x4D, fbits);
    gifs.PackAD(0x4F, D_0036DC20.zbuf);
    gifs.PackAD(0x19, xyoffset.word);
    gifs.PackAD(0x41, D_0036DC20.scissor);
    gifs.AddPrimEnd();
    int values[12];
    memset(values, 0, sizeof(values));
    TEX texture;
    TEX a = texture;
    a.bits.TBP0 = (int)(frame & 0x1FF) << 5;
    a.bits.TBW = (frame >> 16) & 0x3F;
    a.bits.PSM = 0;
    a.bits.TW = 10;
    a.bits.TH = 10;
    a.bits.TCC = 1;
    a.bits.TFX = 0;
    values[9] = mask;
    values[2] = (int)a.word;
    values[0] = (int)frame;
    values[1] = (int)frame2;
    TEX b = a;
    b.bits.PSM = 2;
    values[6] = (int)b.word;
    TEX c = b;
    c.bits.TBP0 = (int)(frame2 & 0x1FF) << 5;
    c.bits.TBW = (frame2 >> 16) & 0x3F;
    c.bits.PSM = 0;
    values[4] = (int)((frame & ~0x3F000000UL) | 0x02000000UL);
    values[5] = (int)((frame2 & ~0x3F000000UL) | 0x02000000UL);
    values[3] = (int)c.word;
    TEX d = c;
    d.bits.PSM = 2;
    values[7] = (int)d.word;
    VIFS vifs;
    vifs.AllocStatic(vifCount, vifBuffer);
    vifs.AddDmaCnt();
    vifs.AddVifFlusha();
    vifs.AddVifDirectRefs(gifCount, gifBuffer, 0);
    vifs.AddVifBaseOffset(0, 0);
    vifs.AddVifUnpack(UPK_V4_32, 3, values, 0xC);
    vifs.EndDmaCnt();
    vifs.AddDmaRet();
}
