// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0018E0B8 (A36): port of Sly 2 func_001681F8 (src/hand there) without its fNever stand-in; Sly 3 adds the tick==-2 skip,
// flag 0x2000, and the sphere-center copy read through the X/Y/Z getters (by-value U inline, as func_00192FD8).
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
union U
{
    qword q;
    float f[4];
};
struct M3
{
    U r[3];
};
struct M4
{
    U r[4];
};
struct V3
{
    float f[3];
};
struct SPHERE
{
    V3 center;
    float radius;
};
struct DESC
{
    char pad[8];
    void *chain;
    char padC[8];
};
struct XF
{
    char pad[0x40];
    M4 matrix;
};
struct ENTRY
{
    int unknown;
    XF *transform;
    M4 *parent;
    uint flags;
    char *matrixData;
    int word;
    char pad18[0xC];
    U *sphere;
};
struct LOCAL_SPHERE
{
    SPHERE sphere;
    char pad[8];
};
struct PACKETS
{
    char pad[0x38];
    int count;
    DESC *descriptors;
    ENTRY *entries;
    LOCAL_SPHERE *spheres;
    int pad48;
    int tick;
};
struct PACKET
{
    int word;
    int reserved[3];
    U sphere;
    M4 matrix;
};
struct DMA
{
    char pad[0xC];
    uchar *pb;
};
struct RPL
{
    int kind, pad4;
    uchar *pb;
    void *chain;
};
extern DMA D_0036C308;
extern int D_00479978;
extern "C" {
void CopyAb(void *pvDst, const void *pvSrc, uint cb);
void *Memcpy(void *pvDst, const void *pvSrc, uint cb) __asm__("memcpy");
M4 *func_0011D558(M4 *pmatDst, const M4 *pmatA, const M4 *pmatB);
float func_0011DF08(const M3 *pmat);
float func_002BE308(U *pv);
float func_002BE310(U *pv);
float func_002BE318(U *pv);
RPL *func_00209B60(void);
}
static inline qword QwTransformPos(M4 *pmat, qword qwPos)
{
    qword qwResult;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(qwResult)
            : "j"(pmat->r[0].q), "j"(pmat->r[1].q), "j"(pmat->r[2].q), "j"(pmat->r[3].q), "j"(qwPos));
    return qwResult;
}
static inline void CopyQws(uint *pwDst, const uint *pwSrc, int cw)
{
    // empty do-while(0) (as left by a statement macro): its loop notes keep later setup below the tag/pb stores
    do
    {
    } while (0);
    for (int k = 0; k < cw; k += 4)
    {
        uint w0 = pwSrc[0];
        uint w1 = pwSrc[1];
        uint w2 = pwSrc[2];
        uint w3 = pwSrc[3];
        pwSrc += 4;
        pwDst[0] = w0;
        pwDst[1] = w1;
        pwDst[2] = w2;
        pwDst[3] = w3;
        pwDst += 4;
    }
}
template <uint TAG> static inline void UnpackQws(const void *pv, int cw)
{
    DMA *pdma = &D_0036C308;
    *(uint *)pdma->pb = TAG;
    pdma->pb += 4;
    CopyQws((uint *)pdma->pb, (const uint *)pv, cw);
    pdma->pb += cw * 4;
}
static inline M4 ModelMatrix(const ENTRY *entry) return model
{
    const M4 *parent = entry->parent;
    Memcpy(&model, &entry->transform->matrix, sizeof(M4));
    if (parent)
    {
        M4 product;
        func_0011D558(&product, &model, parent);
        Memcpy(&model, &product, sizeof(M4));
    }
}
static inline void WriteVertex(U *destination, U value)
{
    float x = func_002BE308(&value);
    float y = func_002BE310(&value);
    float z = func_002BE318(&value);
    destination->f[0] = x; destination->f[1] = y; destination->f[2] = z;
}
extern "C" void func_0018E0B8(PACKETS *p)
{
    int i;
    if (p->tick != -2)
    for (i = 0; i < p->count; i++)
    {
        DESC *descriptor = &p->descriptors[i];
        ENTRY *entry = &p->entries[i];
        PACKET packet;
        if (!descriptor->chain)
            continue;
        packet.word = entry->word;
        if (entry->flags & 0x2000)
            CopyAb(&packet.matrix, entry->matrixData + 0x14, sizeof(M4));
        else
            packet.matrix = ModelMatrix(entry);
        if (entry->sphere)
        {
            WriteVertex(&packet.sphere, *entry->sphere);
            packet.sphere.f[3] = entry->sphere->f[3];
        }
        else
        {
            // a stride variable (not the constant in the index) is what loop.c hoists into s7
            int sphereStride = sizeof(LOCAL_SPHERE);
            LOCAL_SPHERE *sphere = (LOCAL_SPHERE *)((char *)p->spheres + i * sphereStride);
            U center;
            CopyAb(&center, &sphere->sphere.center, sizeof(V3));
            packet.sphere.q = QwTransformPos(&packet.matrix, center.q);
            packet.sphere.f[3] = func_0011DF08((const M3 *)&packet.matrix) * sphere->sphere.radius;
        }
        ulong *ptag = (ulong *)D_0036C308.pb;
        *ptag = 0x10000000;
        D_0036C308.pb += 0x10;
        UnpackQws<0x6C06C301>(&packet, sizeof(PACKET) / sizeof(uint));
        {
            DMA *pdma = &D_0036C308;
            for (uchar *pbPad = pdma->pb; (uint)pbPad & 0xF; pbPad = pdma->pb)
            {
                *(uint *)pbPad = 0;
                pdma->pb += 4;
            }
        }
        *(uint *)ptag |= ((D_0036C308.pb - (uchar *)ptag) >> 4) - 1;
        *(ulong *)D_0036C308.pb = 0x60000000;
        D_0036C308.pb += 0x10;
        RPL *prpl = func_00209B60();
        prpl->pb = (uchar *)ptag;
        prpl->kind = 0;
        prpl->pad4 = 0;
        prpl->chain = descriptor->chain;
    }
    p->tick = D_00479978;
}
