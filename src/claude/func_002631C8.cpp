// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002631C8: reads a sprite root's groups from the stream (Sly 3 form of Sly 2 func_00214460).
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned long ulong64 __attribute__((mode(DI)));
struct BIS;
struct HEAP;
struct GROUP;
struct ROOT;
struct FRAME { char fields[0x70]; };
struct V3 { float x, y, z; } __attribute__((aligned(16)));
struct M3 { V3 row[3]; };
struct M23 { float a[6]; } __attribute__((aligned(16)));
struct RGBA_RAW { uchar r, g, b, a; };
union RGBA { uint word; RGBA_RAW raw; } __attribute__((aligned(16)));
struct COLORS { RGBA_RAW first, second; };
struct ITEM {
    ulong64 b0 : 8;
    ulong64 b8 : 6;
    ulong64 b14 : 10;
    ulong64 b24 : 7;
    ulong64 b31 : 1;
    ulong64 hi : 32;
    char pad8[8];
    M23 matrix;
};
struct KEY {
    float time;
    uint itemCount : 8;
    uint colorCount : 8;
    uint byteCount : 8;
    uint f24 : 1;
    uint f25 : 3;
    int id;
    ITEM *items;
};
struct ANIM { ushort count, pad2; KEY *keys; float duration; GROUP *group; int id; };
struct REUSE { int count; FRAME *frames; short index, phase; void *previous; int elapsed; int pad14; };
struct GROUP { ushort animCount, reuseCount; ANIM *animations; REUSE *reuse; char padC[0x14]; int index; ROOT *owner; int first; int pad2C; };
struct ROOT { char pad0[0x70]; ushort groupCount, pad72; GROUP *groups; char pad78[0xB4 - 0x78]; HEAP *heap; };
int U16Read(BIS *) asm("U16Read__18CBinaryInputStream");
int S32Read(BIS *) asm("S32Read__18CBinaryInputStream");
uint U32Read(BIS *) asm("U32Read__18CBinaryInputStream");
int U8Read(BIS *) asm("U8Read__18CBinaryInputStream");
float F32Read(BIS *) asm("F32Read__18CBinaryInputStream");
void ReadMatrix(BIS *, M3 *) asm("ReadMatrix__18CBinaryInputStreamP7MATRIX3");
void *PvAllocClear(HEAP *, int, int) asm("PvAllocClear__FP4HEAPii");
extern "C" {
void func_002643F8(FRAME *);
void func_00236970(RGBA *);
}
static inline void CopyXY(M23 *dst, const M3 &src)
{
    dst->a[0] = src.row[0].x; dst->a[1] = src.row[0].y;
    dst->a[2] = src.row[1].x; dst->a[3] = src.row[1].y;
    dst->a[4] = src.row[2].x; dst->a[5] = src.row[2].y;
}
extern "C" void func_002631C8(ROOT *root, BIS *stream)
{
    int i, j, k, m, a;
    root->groupCount = U16Read(stream);
    root->groups = (GROUP *)PvAllocClear(root->heap, (int)root->groupCount * 0x30, 0x1C);
    for (i = 0; i < root->groupCount; i++) {
        GROUP *group = &root->groups[i];
        group->owner = root;
        group->first = (i == 0);
        group->reuseCount = U16Read(stream);
        group->reuse = (REUSE *)PvAllocClear(root->heap, (int)group->reuseCount * 0x18, 0x1C);
        int count = U16Read(stream);
        for (j = 0; j < group->reuseCount; j++) {
            REUSE *reuse = &group->reuse[j];
            reuse->index = -1;
            reuse->previous = 0;
            reuse->phase = 0;
            reuse->elapsed = 0;
            reuse->count = count;
            reuse->frames = (FRAME *)PvAllocClear(root->heap, count * 0x70, 0x1A);
            for (m = 0; m < reuse->count; m++)
                func_002643F8(&reuse->frames[m]);
        }
        group->animCount = U16Read(stream);
        group->animations = (ANIM *)PvAllocClear(root->heap, (int)group->animCount * 0x14, 0x1C);
        group->index = -1;
        for (a = 0; a < group->animCount; a++) {
            ANIM *animation = &group->animations[a];
            animation->group = group;
            animation->duration = F32Read(stream);
            animation->id = S32Read(stream);
            animation->count = U16Read(stream);
            animation->keys = (KEY *)PvAllocClear(root->heap, (animation->count & 0xFFFF) * 0x10, 0x1C);
            for (k = 0; k < animation->count; k++) {
                KEY *key = &animation->keys[k];
                key->time = F32Read(stream);
                key->itemCount = U8Read(stream);
                key->colorCount = U8Read(stream);
                key->byteCount = U8Read(stream);
                key->f24 = U8Read(stream);
                key->f25 = U8Read(stream);
                {
                    // The target keeps a dead `lui v0,0x400` (f25 = 2) when f25 != 1; zero-instruction asm
                    // reproduces it. Passing t as well keeps the masked field in its own register (v1).
                    uint t = key->f25 << 25;
                    if (t != 0x2000000)
                        __asm__ __volatile__("" : : "r"(2 << 25), "r"(t));
                }
                key->id = S32Read(stream);
                __asm__ __volatile__(""); // zero-instruction barrier: keeps the next constants after the call
                ITEM *items = (ITEM *)PvAllocClear(root->heap, key->itemCount * 0x30 + key->colorCount * 8 + key->byteCount, 0x1C);
                key->items = items;
                COLORS *colors = (COLORS *)&items[key->itemCount];
                uchar *bytes = (uchar *)&colors[key->colorCount];
                for (int n = 0; n < key->itemCount; n++) {
                    ITEM *item = &items[n];
                    item->b14 = U16Read(stream);
                    item->b0 = U8Read(stream);
                    item->b8 = U8Read(stream);
                    item->b31 = U8Read(stream);
                    int alpha = U8Read(stream);
                    if (alpha >= 0x7F)
                        item->b24 = 0x7F;
                    else
                        item->b24 = alpha;
                    item->hi = S32Read(stream);
                    M3 raw;
                    ReadMatrix(stream, &raw);
                    M3 matrix = raw;
                    CopyXY(&item->matrix, matrix);
                }
                for (m = 0; m < key->colorCount; m++) {
                    RGBA second, first;
                    second.word = U32Read(stream);
                    first.word = U32Read(stream);
                    func_00236970(&second);
                    func_00236970(&first);
                    colors[m].second = second.raw;
                    colors[m].first = first.raw;
                }
                for (m = 0; m < key->byteCount; m++) {
                    uchar *dst = &bytes[m];
                    *dst = U8Read(stream);
                }
            }
        }
    }
}
