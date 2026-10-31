// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_0016CF78): load a skinned mesh part (with bone weights) into a VIF packet.
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char byte;
typedef int qword __attribute__((mode(TI)));
union QW { ulong aul[2]; uint aun[4]; float ag[4]; } __attribute__((aligned(16)));
union U { qword q; float f[4]; };
struct VECTOR;
enum UPK { UPK_V4_32 = 12, UPK_V4_16 = 13 };
struct HEAP;
class CBinaryInputStream {
public:
    uint U8Read();
    uint U16Read();
    int S16Read();
    void Read(int cb, void *pv);
    void ReadVector(VECTOR *pvec);
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
};
struct FRAME { char b; FRAME(); ~FRAME(); };
struct PARAM { float value; int pad, kind; };
struct D { char kind, count; ushort flags; void *pad4; void *pad8; int base; int words; };
struct E { char pad[0x10]; QW *chain; };
struct HEADER { ushort flags, base, vertices, pad6, pad8, padA, padC, padE, weight, end, segments[2], bones[4]; };
struct OWNER;
struct SPHERE;
struct OBJECT { char pad[0x1C]; int count; };
struct REQUEST { int bytes, alignment; REQUEST(int cb, int a) : bytes(cb), alignment(a) {} void *Allocate(); };
extern "C" {
extern char D_00000000[], D_000019C8[], D_00001B20[];
extern QW D_0036DBC0;
extern uint D_00345000[];
extern UPK D_00345018[];
void *memset(void *, int, uint);
void *PvAllocSlot(const REQUEST &) asm("PvAllocSlot__FP8ALLOCREQ");
void CopyAb(void *, const void *, uint);
OBJECT *func_00235F68(int);
int func_00235CC0(OBJECT *, int, int, VIFS *);
float func_002BE308(const U *);
float func_002BE310(const U *);
float func_002BE318(const U *);
void func_0018F6B8(OWNER *, D *, E *, SPHERE *, int, int, int, int, CBinaryInputStream *);
void func_00192FD8(OWNER *p, D *desc, E *entry, PARAM *param, SPHERE *sphere, int groups, CBinaryInputStream *stream, HEAP *pheap);
}
inline void *REQUEST::Allocate() { return PvAllocSlot(*this); }
static inline void *Allocate(int bytes) { return REQUEST(bytes, 16).Allocate(); }
static inline void WriteVertex(U *destination, U value)
{
    float x = func_002BE308(&value);
    float y = func_002BE310(&value);
    float z = func_002BE318(&value);
    destination->f[0] = x; destination->f[1] = y; destination->f[2] = z;
}
void func_00192FD8(OWNER *p, D *desc, E *entry, PARAM *param, SPHERE *sphere, int groups, CBinaryInputStream *stream, HEAP *pheap)
{
    int vertex;
    int index;
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
        HEADER *header;
        char *weights;
        U *positions;
        vifs.UnpackHelper(UPK_V4_16, 4, 10, 0, (uint **)&header);
        memset(header, 0, 32);
        switch (part) {
        case 0:
            header->flags = 1;
            if (subCount == 1)
                header->flags |= 8;
            switch (param->kind) {
            case 2:
                header->flags |= 0x400;
                break;
            case 3:
                header->flags |= 0x1000;
                break;
            }
            break;
        case 1:
            header->flags = 2;
            break;
        }
        header->base = base;
        OBJECT *object = func_00235F68(stream->U16Read());
        int vertices = stream->U8Read();
        int vectorCount = stream->U8Read();
        U *vectors = (U *)Allocate(vectorCount * sizeof(U));
        if (vectorCount > 0) {
            U *cursor = vectors;
            index = vectorCount;
            do {
                stream->ReadVector((VECTOR *)cursor);
                --index;
                ++cursor;
            } while (index);
        }
        char *boneWeights;
        int bones = desc->count < 4 ? desc->count : 4;
        if (desc->count) {
            int b;
            for (b = 0; b < 4; b++) {
                int bone = stream->U8Read();
                HEADER *slot = (HEADER *)((uint)header + b * 2);
                slot->bones[0] = (ushort)desc->base + bone * 4;
            }
            int bytes = bones * vectorCount;
            boneWeights = (char *)Allocate(bytes);
            stream->Read(bytes, boneWeights);
        } else
            boneWeights = 0;
        byte *indices = (byte *)Allocate(vertices);
        stream->Read(vertices, indices);
        int flagBytes = ((vertices + 31) / 32) * 4;
        uint *flags = (uint *)Allocate(flagBytes);
        stream->Read(flagBytes, flags);
        uint *flagCursor = flags;
        uint mask = 1;
        int current = base;
        for (int segment = 0; segment < object->count; segment++) {
            HEADER *slot = (HEADER *)((uint)header + segment * 2);
            slot->segments[0] = current;
            current += func_00235CC0(object, segment, current, &vifs);
        }
        ++current;
        header->weight = current;
        current += 2 * vertices;
        header->end = current;
        header->vertices = vertices;
        vifs.AddVifStcycl(1, 2);
        if (desc->count) {
            int small = bones < 4;
            if (small) {
                vifs.AddVifStrow(&D_0036DBC0);
                vifs.AddVifStmask(D_00345000[bones]);
            }
            vifs.UnpackHelper(D_00345018[bones], vertices, header->weight, 0, (uint **)&weights);
            if (small)
                vifs.AddVifStmask(0);
        }
        vifs.UnpackHelper(UPK_V4_32, vertices, header->weight + 1, 0, (uint **)&positions);
        vifs.AddVifStcycl(1, 1);
        for (vertex = 0; vertex < vertices; vertex++) {
            index = indices[vertex];
            WriteVertex(&positions[vertex], vectors[index]);
            if (*flagCursor & mask)
                positions[vertex].f[3] = 8421376.0f;
            else
                positions[vertex].f[3] = 8417280.0f;
            mask <<= 1;
            if (!mask) {
                ++flagCursor;
                mask = 1;
            }
        }
        if (desc->count) {
            for (vertex = 0; vertex < vertices; vertex++) {
                index = indices[vertex];
                CopyAb(weights + vertex * bones, boneWeights + index * bones, bones);
            }
        }
        vifs.AddVifMscal(D_00000000);
        vifs.AddVifMscal(D_000019C8);
        vifs.AddVifMscal(D_00001B20);
    }
    vifs.EndDmaCnt();
    vifs.AddDmaRet();
    vifs.DetachCopySw(pheap, &desc->words, &data, &entry->chain);
    func_0018F6B8(p, desc, entry, sphere, groups, 0, 0, 0, stream);
}
