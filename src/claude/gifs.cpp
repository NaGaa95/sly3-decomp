// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Sly 2 reference: /home/claude/decomp src/P2/gifs.cpp
#define NULL 0
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
union QW {
    ulong aul[2];
    long al[2];
    uint aui[4];
    uint aun[4];
    int an[4];
    float ag[4];
} __attribute__((aligned(16)));
struct HEAP;
struct ALLOCREQ { int cb; int cbAlign; };
class DMAS
{
public:
    uchar *m_pbMax;
    uchar *m_ab;
    QW *m_pqwCnt;
    uchar *m_pb;
    int m_fPad;
    int m_fEndPrim;
    DMAS();
    void Clear();
    void Reset();
    void AllocSw(int cqw);
    void AllocStatic(int cqw, QW *aqw);
    void Detach(int *pcqw, QW **paqw);
    void DetachCopySw(int *pcqw, QW **paqw, QW **paqwCopy);
    void DetachCopySw(HEAP *pheap, int *pcqw, QW **paqw, QW **paqwCopy);
    void Flush();
    void AddDmaCnt();
    void AddDmaRefs(int cqw, QW *aqw);
    void AddDmaCall(QW *aqw);
    void AddDmaRet();
    void AddDmaBulk(int cqw, QW *aqw);
    void AddDmaEnd();
    void EndDmaCnt();
    virtual void EndPrim(int n);
};
class GIFS : public DMAS
{
public:
    QW *m_pqwPrim;
    uint m_creg;
    uint m_cregAll;

    GIFS();
    void AddPrimEnd();
    virtual void EndPrim(int fEOP);
    void CheckReg(int fExpectPack, int regExpect);
    void AddPrimBulk(int prim, int c, int creg, ulong regs, QW **paqwBulk);
    void AddPrimPack(int prim, int creg, ulong regs);
    void AddGifTag(int prim, int c, int creg, ulong regs, uint fEOP);
    void PackRGBA(uint rgba);
    void PackUV(int u, int v);
    void PackSTQ(float s, float t, float q);
    void PackXYZ(int x, int y, int z);
    void PackXYZF(int x, int y, int z, int fog);
    void PackAD(long a, long d);
    void AddPrimList(int creg, ulong regs);
    void ListRGBAQ(uint rgba, float q);
    void ListUV(int u, int v);
    void ListXYZ(int x, int y, int z);
    void ListXYZF(int x, int y, int z, int fog);
    void AddImage(int cqw);
};

void GIFS::CheckReg(int fExpectPack, int regExpect)
{
    m_cregAll++;
}

void GIFS::PackRGBA(uint rgba)
{
    CheckReg(1, 1);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aun[0] = rgba & 0xff;
    pqw->aun[1] = (rgba & 0xff00) >> 8;
    pqw->aun[2] = (rgba >> 16) & 0xff;
    pqw->aun[3] = (rgba >> 24) & 0xff;
}

void GIFS::PackUV(int u, int v)
{
    CheckReg(1, 3);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->an[0] = u;
    pqw->an[1] = v;
}

void GIFS::PackSTQ(float s, float t, float q)
{
    CheckReg(1, 2);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->ag[0] = s;
    pqw->ag[1] = t;
    pqw->ag[2] = q;
}

void GIFS::PackXYZ(int x, int y, int z)
{
    CheckReg(1, 5);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->an[0] = x;
    pqw->an[1] = y;
    pqw->al[1] = z;
}

void GIFS::PackXYZF(int x, int y, int z, int fog)
{
    CheckReg(1, 4);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->an[0] = x;
    pqw->an[1] = y;
    pqw->an[2] = z;
    pqw->an[3] = (fog & 0xff) << 4;
}

void GIFS::PackAD(long a, long d)
{
    CheckReg(1, 14);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aul[0] = d;
    pqw->aul[1] = a;
}

void GIFS::ListUV(int u, int v)
{
    CheckReg(0, 3);
    ulong *pul = (ulong *)m_pb;
    m_pb = (uchar *)(pul + 1);
    *pul = u | ((ulong)v << 16);
}

GIFS::GIFS()
{
    m_fEndPrim = 1;
    m_pqwPrim = NULL;
    m_creg = 0;
    m_cregAll = 0;
}

void GIFS::AddPrimEnd()
{
    if (m_pqwPrim)
    {
        EndPrim(1);
    }
    else
    {
        AddPrimPack(0, 1, 0xE);
        EndPrim(1);
    }
}

// GIFS::EndPrim (0x18C810) not matched yet: register allocation of c/pqw differs (wip build/claude_wip/gifs.cpp)

void GIFS::AddGifTag(int prim, int c, int creg, ulong regs, uint fEOP)
{
    EndPrim(0);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    ulong tag = c | ((ulong)fEOP << 15);
    ulong tagPrim = ((ulong)prim << 47) | (1L << 46);
    tag |= tagPrim;
    tag |= (ulong)creg << 60;
    pqw->aul[0] = tag;
    pqw->aul[1] = regs;
}

void GIFS::AddPrimPack(int prim, int creg, ulong regs)
{
    EndPrim(0);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    ulong tag = ((ulong)creg << 60) | (1L << 46);
    pqw->aul[0] = ((ulong)prim << 47) | tag;
    pqw->aul[1] = regs;
    m_cregAll = 0;
    m_creg = creg;
    m_pqwPrim = pqw;
}

void GIFS::AddPrimBulk(int prim, int c, int creg, ulong regs, QW **paqwBulk)
{
    EndPrim(0);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    ulong tag = ((ulong)prim << 47) | (1L << 46);
    tag = c | tag;
    tag |= (ulong)creg << 60;
    pqw->aul[1] = regs;
    pqw->aul[0] = tag;
    if (paqwBulk)
    {
        *paqwBulk = (QW *)m_pb;
    }
    m_pb += c * creg * sizeof(QW);
}

void GIFS::AddPrimList(int creg, ulong regs)
{
    EndPrim(0);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aul[1] = regs;
    pqw->aul[0] = ((ulong)creg << 60) | (1L << 58);
    m_creg = creg;
    m_pqwPrim = pqw;
    m_cregAll = 0;
}

void GIFS::ListRGBAQ(uint rgba, float q)
{
    CheckReg(0, 1);
    ulong *pul = (ulong *)m_pb;
    m_pb = (uchar *)(pul + 1);
    *pul = (ulong)rgba | ((ulong)*(uint *)&q << 32);
}

void GIFS::ListXYZ(int x, int y, int z)
{
    CheckReg(0, 5);
    ulong *pul = (ulong *)m_pb;
    m_pb = (uchar *)(pul + 1);
    *pul = x | ((ulong)y << 16) | ((ulong)z << 32);
}

void GIFS::ListXYZF(int x, int y, int z, int fog)
{
    CheckReg(0, 4);
    ulong *pul = (ulong *)m_pb;
    m_pb = (uchar *)(pul + 1);
    *pul = x | ((ulong)y << 16) | ((ulong)z << 32) | ((ulong)fog << 56);
}

void GIFS::AddImage(int cqw)
{
    EndPrim(0);
    QW *pqw = (QW *)m_pb;
    m_pb = (uchar *)(pqw + 1);
    pqw->aul[0] = cqw | (2L << 58);
    pqw->aul[1] = 0;
}
