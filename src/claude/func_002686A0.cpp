// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002686A0: Sly 3 form of Sly 2 func_00219400 - apply one animation key's poses to the reuse slot's items
// (called by func_00269418). Sly 3 packs each pose into a 0x30-byte record: a 64-bit header (index:8, link offset:6, sprite
// id:10, colour index:7 (0x7F = none), interpolate:1, selected:32) and the M23 matrix at +0x10; the key's COLORS table follows
// its pose array. New in Sly 3: a pose whose sprite id differs from the item's sprite releases it (func_002646F8), resets the
// item (func_002643F8), sets the link kinds there, and is drawn through func_00264478 instead of func_002645A0.
// Matching notes: the header tests are macros on the 64-bit word (inline bool/int returns give setcc); one zero-instruction
// keep-alive asm on j right before the item stores gives j its global-alloc priority (fp; fNew spilled at 0xD0) and puts the
// increment where the game has it; func_002645A0's float argument sits third in this prototype (argument move order).
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned int UDI __attribute__((mode(DI)));
struct RGBA_RAW { uchar r, g, b, a; };
struct RGBA {
    uchar r, g, b, a;
    RGBA() {}
    RGBA(const RGBA &c) { *(RGBA_RAW *)this = *(const RGBA_RAW *)&c; }
    RGBA(const RGBA_RAW &c) { *(RGBA_RAW *)this = c; }
    const RGBA_RAW &Raw() const { return *(const RGBA_RAW *)this; }
    RGBA &operator=(const RGBA &c) { *(RGBA_RAW *)this = *(const RGBA_RAW *)&c; return *this; }
} __attribute__((aligned(16)));
struct M23 { float a[6]; } __attribute__((aligned(16)));
struct SPRITE { int id, kind; char pad8[0x10]; M23 *matrix18; int field1C; M23 *matrix20; char pad24[0xC]; };
struct ITEM {
    RGBA_RAW additive, multiply;
    char pad8[8];
    M23 matrix;
    SPRITE *sprite;
    int kind;
    float previousTime;
    RGBA_RAW previousAdditive, previousMultiply;
    M23 *previousMatrix;
    float nextTime;
    RGBA_RAW nextAdditive, nextMultiply;
    M23 *nextMatrix;
    int index;
    float cachedTime;
    uchar interpolate, offset;
    char pad62[2];
    int selected;
    int flags, pad6C;
};
struct REUSE { int count; ITEM *items; ushort index, phase; float time; int field10, field14; };
struct ROOT { char pad[0x44]; SPRITE *sprites; };
struct GROUP { char pad0[8]; REUSE *reuse; char padC[0x18]; ROOT *owner; };
struct KEYPOSE { UDI bits; M23 matrix; };
struct COLORS { RGBA_RAW multiply, additive; };
struct KEY { float time; uchar itemCount; char pad5[7]; KEYPOSE *items; };
struct ANIM { ushort count, pad2; KEY *keys; float duration; GROUP *group; int id; };
struct LM { float lo, hi; };

extern "C" {
void func_0011AD68(int *);
void *memset(void *, int, unsigned int);
float func_0011EE68(LM *, float);
void func_002646F8(SPRITE *, ITEM *);
void func_002643F8(ITEM *);
void func_002679B8(RGBA *, RGBA *, RGBA *, RGBA *, RGBA *, RGBA *);
void func_00264478(SPRITE *, ITEM *, M23 *, RGBA, RGBA);
void func_002645A0(SPRITE *, ITEM *, float, M23 *, RGBA, RGBA);
}

static inline int NLerp(float t, int previous, int next)
{
    if (previous == next)
        return next;
    if (previous < next)
        return previous + (int)(t * ((float)next + 0.999f - (float)previous));
    return next + (int)((1.0f - t) * ((float)previous + 0.999f - (float)next));
}
static inline RGBA BlendColors(float t, RGBA previous, RGBA next)
{
    RGBA result;
    result.r = NLerp(t, previous.r, next.r);
    result.g = NLerp(t, previous.g, next.g);
    result.b = NLerp(t, previous.b, next.b);
    result.a = NLerp(t, previous.a, next.a);
    return result;
}
static inline M23 BlendMatrix(float t, const M23 &previous, const M23 &next)
{
    M23 result;
    for (int n = 0; n < 6; n++)
        result.a[n] = (1.0f - t) * previous.a[n] + t * next.a[n];
    return result;
}
static inline M23 Mul(const M23 &q, const M23 &n)
{
    float m0 = q.a[0], m1 = q.a[1], m2 = q.a[2], m3 = q.a[3], m4 = q.a[4], m5 = q.a[5];
    M23 r;
    r.a[0] = m0 * n.a[0] + m1 * n.a[2];
    r.a[1] = m0 * n.a[1] + m1 * n.a[3];
    r.a[2] = m2 * n.a[0] + m3 * n.a[2];
    r.a[3] = m2 * n.a[1] + m3 * n.a[3];
    r.a[4] = m4 * n.a[0] + m5 * n.a[2] + n.a[4];
    r.a[5] = m4 * n.a[1] + m5 * n.a[3] + n.a[5];
    return r;
}
static inline M23 *SpriteMatrix(SPRITE *sprite)
{
    M23 *pmat = 0;
    switch (sprite->kind) {
    case 1:
        pmat = sprite->matrix20;
        break;
    case 7:
        pmat = sprite->matrix18;
        break;
    }
    return pmat;
}
static inline int PoseIndex(KEYPOSE *p) { return *(uchar *)p; }
static inline int PoseOffset(KEYPOSE *p) { return (int)(p->bits >> 8) & 0x3F; }
static inline int PoseId(KEYPOSE *p) { return (int)(p->bits >> 14) & 0x3FF; }
#define FPoseColor(p) (((p)->bits & 0x7F000000) != 0x7F000000)
static inline int PoseColor(KEYPOSE *p) { return (int)(p->bits >> 24) & 0x7F; }
#define FPoseInterpolate(p) ((p)->bits & 0x80000000)
static inline int PoseInterpolate(KEYPOSE *p) { return (int)(p->bits >> 31) & 1; }
static inline COLORS *KeyColors(KEY *key) { return (COLORS *)&key->items[key->itemCount]; }

extern "C" void func_002686A0(float time, float duration, ANIM *animation, int phase, int index, M23 *parent, const RGBA *additive, const RGBA *multiply)
{
    uint j = 0;
    ITEM *items = animation->group->reuse[index].items;
    KEY *key = &animation->keys[phase];
    M23 matrix;
    RGBA outputAdditive, outputMultiply, currentAdditive, currentMultiply;

    if (key->itemCount) do {
        KEYPOSE *pose = &key->items[j];
        int fNew = 0;
        int entryIndex = PoseIndex(pose);
        ITEM *item = &items[entryIndex];
        int linkOffset = PoseOffset(pose);
        int id = PoseId(pose);
        if (id > 0) {
            if (!item->sprite)
                fNew = 1;
            else if (item->sprite->id != id) {
                func_002646F8(item->sprite, item);
                fNew = 1;
            }
        }
        if (fNew) {
            func_002643F8(item);
            if (linkOffset) {
                item->offset = linkOffset;
                item->kind = 1;
                items[entryIndex + linkOffset].kind = 4;
            }
        }
        if (FPoseColor(pose)) {
            COLORS *colors = &KeyColors(key)[PoseColor(pose)];
            item->previousAdditive = colors->additive;
            *(RGBA_RAW *)&currentAdditive = item->previousAdditive;
            item->previousMultiply = colors->multiply;
            *(RGBA_RAW *)&currentMultiply = item->previousMultiply;
        } else {
            *(uint *)&item->previousAdditive = 0x7F7F7F7F;
            *(uint *)&currentAdditive = 0x7F7F7F7F;
            *(uint *)&item->previousMultiply = 0xFFFFFFFF;
            *(uint *)&currentMultiply = 0xFFFFFFFF;
        }
        item->previousMatrix = &pose->matrix;
        item->previousTime = key->time;
        item->nextMatrix = 0;
        item->nextTime = 0.0f;

        if (FPoseInterpolate(pose)) {
            int nextKey = phase + 1;
            if (nextKey < animation->count) {
                do {
                    KEY *future = &animation->keys[nextKey];
                    for (uint n = 0; n < future->itemCount; n++) {
                        KEYPOSE *futurePose = &future->items[n];
                        if (PoseIndex(futurePose) == entryIndex) {
                            item->nextMatrix = &futurePose->matrix;
                            item->nextTime = future->time;
                            if (FPoseColor(futurePose)) {
                                COLORS *colors = &KeyColors(future)[PoseColor(futurePose)];
                                item->nextAdditive = colors->additive;
                                item->nextMultiply = colors->multiply;
                            } else {
                                item->nextAdditive = item->previousAdditive;
                                item->nextMultiply = item->previousMultiply;
                            }
                            break;
                        }
                    }
                    nextKey++;
                } while (nextKey < animation->count && !item->nextMatrix);
            }
        }

        if (FPoseInterpolate(pose) && item->nextMatrix && item->previousTime < item->nextTime) {
            LM copy;
            float limited;
            {
                LM bounds;
                memset(&bounds, 0, 8);
                bounds.lo = item->previousTime;
                bounds.hi = item->nextTime;
                copy = bounds;
                limited = func_0011EE68(&copy, duration);
            }
            float fraction = (limited - item->previousTime) / (item->nextTime - item->previousTime);
            matrix = BlendMatrix(fraction, *item->previousMatrix, *item->nextMatrix);
            currentAdditive = BlendColors(fraction, RGBA(item->previousAdditive), RGBA(item->nextAdditive));
            currentMultiply = BlendColors(fraction, RGBA(item->previousMultiply), RGBA(item->nextMultiply));
        } else {
            matrix = *item->previousMatrix;
            *(RGBA_RAW *)&currentAdditive = item->previousAdditive;
            *(RGBA_RAW *)&currentMultiply = item->previousMultiply;
        }
        matrix = Mul(matrix, *parent);
        {
            RGBA inputMultiply(*multiply), inputAdditive(*additive), localMultiply(currentMultiply), localAdditive(currentAdditive);
            func_002679B8(&inputMultiply, &inputAdditive, &localMultiply, &localAdditive, &outputMultiply, &outputAdditive);
        }
        if (fNew)
            func_00264478(&animation->group->owner->sprites[id], item, &matrix, outputAdditive, outputMultiply);
        else
            func_002645A0(item->sprite, item, duration, &matrix, outputAdditive, outputMultiply);
        if (item->sprite) {
            M23 *pmat = SpriteMatrix(item->sprite);
            if (pmat)
                matrix = Mul(matrix, *pmat);
        }
        __asm__("" : : "r"(j), "r"(j));   /* zero-instruction keep-alive (allocation/scheduling only) */
        item->cachedTime = time;
        item->matrix = matrix;
        item->additive = outputAdditive.Raw();
        item->multiply = outputMultiply.Raw();
        item->interpolate = PoseInterpolate(pose);
        item->selected = *((int *)pose + 1);
        func_0011AD68(&item->flags);
    } while (++j < key->itemCount);
}
