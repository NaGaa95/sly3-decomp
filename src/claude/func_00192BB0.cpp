// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_0016CAA0): load a skinned mesh part into a VIF packet.
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
union QW { ulong aul[2]; uint aun[4]; float ag[4]; } __attribute__((aligned(16)));
enum UPK { UPK_V3_32 = 8, UPK_V4_16 = 13, UPK_V4_8 = 14 };
struct HEAP;
class CBinaryInputStream {
public:
    uint U8Read();
    uint U16Read();
    int S16Read();
};
class DMAS {
public:
    unsigned char *m_pbMax, *m_ab; QW *m_pqwCnt; unsigned char *m_pb; int m_fPad, m_fEndPrim;
    void AllocSw(int cqw);
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
    void AddVifStcycl(int wl, int cl);
    void AddVifStrow(QW *pqw);
    void AddVifStmask(uint unMask);
    void UnpackHelper(UPK upk, int c, int iqw, int *pcb, uint **ppun);
    void AddVifUnpack(UPK upk, int c, CBinaryInputStream *pbis, int iqw);
};
struct FRAME { char b; FRAME(); ~FRAME(); };
struct D { char kind, count; ushort flags; void *pad4; void *pad8; int base; int words; };
struct E { char pad[0x10]; QW *chain; };
struct OWNER;
struct SPHERE;
struct OBJECT { char pad[0x1C]; int count; };
extern "C" {
extern char D_00000000[], D_000019C8[], D_00001B20[];
extern QW D_0036DBC0;
extern uint D_00345000[];
extern UPK D_00345018[];
void *memset(void *, int, uint);
OBJECT *func_00235F68(int);
int func_00235CC0(OBJECT *, int, int, VIFS *);
void func_0018F6B8(OWNER *, D *, E *, SPHERE *, int, int, int, int, CBinaryInputStream *);
void func_00192BB0(OWNER *p, D *desc, E *entry, void *pv, SPHERE *sphere, int groups, CBinaryInputStream *stream, HEAP *pheap);
}
void func_00192BB0(OWNER *p, D *desc, E *entry, void *pv, SPHERE *sphere, int groups, CBinaryInputStream *stream, HEAP *pheap)
{
    VIFS vifs;
    FRAME outer;
    vifs.AllocSw(0x2000);
    vifs.AddDmaCnt();
    int base = 0x1B;
    if (desc->count) {
        desc->base = base;
        base += desc->count * 4;
    }
    int subCount = stream->S16Read();
    QW *data;
    for (int part = 0; part < subCount; part++) {
        FRAME inner;
        ushort *header;
        vifs.UnpackHelper(UPK_V4_16, 4, 10, 0, (uint **)&header);
        memset(header, 0, 32);
        switch (part) {
        case 0:
            header[0] |= 1;
            if (subCount == 1)
                header[0] |= 8;
            break;
        case 1:
            header[0] |= 2;
            break;
        }
        if (desc->count)
            header[0] |= 4;
        int current = base;
        header[1] = current;
        OBJECT *object = func_00235F68(stream->U16Read());
        for (int segment = 0; segment < object->count; segment++) {
            { uint off = segment * 2; ((ushort *)((uint)header + off))[10] = current; }
            current += func_00235CC0(object, segment, current, &vifs);
        }
        int vertices = stream->U8Read();
        vifs.AddVifStcycl(1, 2);
        vifs.AddVifUnpack(UPK_V3_32, vertices, stream, current + 1);
        header[4] = current;
        current += vertices * 2;
        header[5] = current;
        if (desc->count) {
            int bones = stream->U8Read();
            int k = 0;
            for (; k < bones; k++) {
                int bone = stream->U8Read();
                { uint off = k * 2; ((ushort *)((uint)header + off))[12] = (ushort)desc->base + bone * 4; }
            }
            for (; k < 4; k++)
                { uint off = k * 2; ((ushort *)((uint)header + off))[12] = header[12]; }
            int small = bones < 4;
            if (small) {
                vifs.AddVifStrow(&D_0036DBC0);
                vifs.AddVifStmask(D_00345000[bones]);
            }
            vifs.AddVifUnpack(D_00345018[bones], vertices, stream, header[4]);
            if (small)
                vifs.AddVifStmask(0);
        }
        vifs.AddVifStcycl(1, 1);
        int colors = stream->U8Read();
        vifs.AddVifUnpack(UPK_V4_8, colors, stream, current);
        header[6] = current;
        current += colors;
        header[7] = current;
        current++;
        header[8] = header[9] = current;
        vifs.AddVifMscal(D_00000000);
        vifs.AddVifMscal(D_000019C8);
        vifs.AddVifMscal(D_00001B20);
    }
    vifs.EndDmaCnt();
    vifs.AddDmaRet();
    vifs.DetachCopySw(pheap, &desc->words, &data, &entry->chain);
    func_0018F6B8(p, desc, entry, sphere, groups, 0, 0, 0, stream);
}
