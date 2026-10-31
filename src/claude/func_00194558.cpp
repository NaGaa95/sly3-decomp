// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_0016E438): load an environment-mapped mesh part into a VIF packet.
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef int qword __attribute__((mode(TI)));
union QW { ulong aul[2]; uint aun[4]; float ag[4]; } __attribute__((aligned(16)));
enum UPK { UPK_V3_32 = 8, UPK_V4_32 = 12, UPK_V4_16 = 13, UPK_V4_8 = 14 };
struct HEAP;
class CBinaryInputStream {
public:
    uint U8Read();
    uint U32Read();
    int S16Read();
};
class DMAS {
public:
    unsigned char *m_pbMax, *m_ab; QW *m_pqwCnt; unsigned char *m_pb; int m_fPad, m_fEndPrim;
    void AllocSw(int cqw);
    void Reset();
    void AddDmaCnt();
    void EndDmaCnt();
    void AddDmaRet();
    void DetachCopySw(HEAP *pheap, int *pcqw, QW **paqw, QW **paqwCopy);
    virtual void EndPrim(int n);
};
class VIFS : public DMAS {
public:
    uint m_unMask;
    VIFS();
    void AddVifMscal(void *pv);
    void AddVifStrow(QW *pqw);
    void AddVifStmask(uint unMask);
    void AddVifUnpack(UPK upk, int c, void *pv, int iqw);
    void AddVifUnpack(UPK upk, int c, CBinaryInputStream *pbis, int iqw);
    void UnpackHelper(UPK upk, int c, int iqw, int *pcb, uint **ppun);
};
class GIFS : public DMAS {
public:
    QW *m_pqwPrim; uint m_creg; uint m_cregAll;
    GIFS();
    virtual void EndPrim(int fEOP);
    void AddPrimPack(int prim, int creg, ulong regs);
    void PackAD(long a, long d);
    void PackRGBA(uint rgba);
    void PackXYZF(int x, int y, int z, int f);
};
struct FRAME { char b; FRAME(); ~FRAME(); };
struct PARAM { float value; int pad, kind; };
struct D { char kind, count; ushort flags; void *pad4; void *pad8; int base; int words; };
struct E { char pad[0x10]; QW *chain; };
struct HEADER { ushort flags, base, pad4, pad6, position, positionEnd, color, end, bones[4]; };
struct OWNER;
struct SPHERE;
struct ENV;
extern "C" {
extern char D_00000000[], D_00000738[], D_000007F0[];
extern ENV D_0036BC10;
extern QW D_0036DBC0;
extern uint D_00345000[];
extern UPK D_00345018[];
void *memset(void *, int, uint);
void func_001692E8(ENV *, float *, float);
void func_0018F6B8(OWNER *, D *, E *, SPHERE *, int, int, int, int, CBinaryInputStream *);
void func_00194558(OWNER *p, D *desc, E *entry, PARAM *param, SPHERE *sphere, int groups, CBinaryInputStream *stream, HEAP *pheap);
}
void func_00194558(OWNER *p, D *desc, E *entry, PARAM *param, SPHERE *sphere, int groups, CBinaryInputStream *stream, HEAP *pheap)
{
    VIFS vifs;
    FRAME outer;
    vifs.AllocSw(0x2000);
    vifs.AddDmaCnt();
    float *environment;
    vifs.UnpackHelper(UPK_V4_32, 1, 9, 0, (uint **)&environment);
    func_001692E8(&D_0036BC10, environment, param->value);
    QW color;
    color.aun[0] = stream->U32Read();
    int base = 0x22;
    GIFS gifs;
    gifs.AllocSw(8);
    gifs.AddPrimPack(0, 2, 0x1EUL);
    gifs.PackAD(0x42L, 0x44L);
    gifs.PackRGBA(color.aun[0]);
    gifs.GIFS::EndPrim(1);
    vifs.AddVifUnpack(UPK_V4_32, ((uint)gifs.m_pb - (uint)gifs.m_ab) >> 4, gifs.m_ab, 0xD);
    gifs.Reset();
    gifs.AddPrimPack(0xC1, 3, 0x44EUL);
    gifs.PackAD(0x47L, 0x73001L);
    gifs.PackXYZF(0, 0, 0, 0);
    gifs.PackXYZF(0, 0, 0, 0);
    gifs.GIFS::EndPrim(0);
    gifs.AddPrimPack(1, 3, 0x44EUL);
    gifs.PackAD(0x47L, 0x72001L);
    gifs.PackXYZF(0, 0, 0, 0);
    gifs.PackXYZF(0, 0, 0, 0);
    gifs.GIFS::EndPrim(1);
    vifs.AddVifUnpack(UPK_V4_32, 2, gifs.m_ab, 0x12);
    vifs.AddVifUnpack(UPK_V4_32, 2, gifs.m_ab + 0x40, 0x16);
    vifs.AddVifUnpack(UPK_V4_32, 2, gifs.m_ab, 0x1A);
    vifs.AddVifUnpack(UPK_V4_32, 2, gifs.m_ab + 0x40, 0x1E);
    if (desc->count) {
        desc->base = base;
        base += desc->count * 4;
    }
    int subCount = stream->S16Read();
    QW *data;
    for (int part = 0; part < subCount; part++) {
        FRAME inner;
        HEADER *header;
        vifs.UnpackHelper(UPK_V4_16, 3, 10, 0, (uint **)&header);
        memset(header, 0, 24);
        switch (part) {
        case 0:
            header->flags |= 1;
            break;
        case 1:
            header->flags |= 2;
            break;
        }
        int current = base;
        header->base = current;
        int vertices = stream->U8Read();
        vifs.AddVifUnpack(UPK_V3_32, vertices, stream, current);
        header->position = current;
        current += vertices;
        header->positionEnd = current;
        if (desc->count) {
            int bones = stream->U8Read();
            int k;
            for (k = 0; k < bones; k++) {
                int bone = stream->U8Read();
                HEADER *slot = (HEADER *)((uint)header + k * 2);
                slot->bones[0] = (ushort)desc->base + bone * 4;
            }
            for (; k < 4; k++) {
                HEADER *slot = (HEADER *)((uint)header + k * 2);
                slot->bones[0] = header->bones[0];
            }
            int small = bones < 4;
            if (small) {
                vifs.AddVifStrow(&D_0036DBC0);
                vifs.AddVifStmask(D_00345000[bones]);
            }
            vifs.AddVifUnpack(D_00345018[bones], vertices, stream, current);
            header->pad4 = current;
            current += vertices;
            if (small)
                vifs.AddVifStmask(0);
        }
        int colors = stream->U8Read();
        vifs.AddVifUnpack(UPK_V4_8, colors, stream, current);
        header->color = current;
        current += colors;
        header->end = current;
        vifs.AddVifMscal(D_00000000);
        vifs.AddVifMscal(D_00000738);
        vifs.AddVifMscal(D_000007F0);
    }
    vifs.EndDmaCnt();
    vifs.AddDmaRet();
    vifs.DetachCopySw(pheap, &desc->words, &data, &entry->chain);
    func_0018F6B8(p, desc, entry, sphere, groups, 0, 0, 0, stream);
}
