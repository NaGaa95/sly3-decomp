// SLY3_CFLAGS: -Os -G0 -ffast-math
// Give an object a slot from the 256-entry free bitmap (if it has none yet), then insert it into the
// tree or, when it can't be inserted now, mark its slot as pending (same routine as Sly 2 func_001A3D00).
typedef int qword __attribute__((mode(TI)));

struct NODE { qword plane; struct NODE *left, *right; int leftLeaf, rightLeaf; };
struct VEntry { short d; short pad; unsigned char *(*pfn)(void *); };
struct OBJ {
    char pad000[0xC]; struct VEntry *vt;
    char pad010[0xD0 - 0x10];
    int xD0;
    char pad0D4[0x108 - 0xD4];
    int slot;           // 0x108, < 0 until a slot is assigned
    char pad10C[0x14C - 0x10C];
    int x14C;
    int x150;
    int pad154;
    float radius;       // 0x158
};
struct SLOTS {
    char pad0000[0x4988];
    struct OBJ *objects[0x100];   // 0x4988
    int disabled;                 // 0x4D88
    int pad4D8C;
    struct NODE *root;            // 0x4D90
    int pad4D94;
    void *leaves;
    int pad4D9C;
    int pending[8];               // 0x4DA0, bit per slot
    unsigned int free[8];         // 0x4DC0, bit per free slot
};

void func_001C5A98(struct SLOTS *s, struct NODE *node, qword pos, float radius, int slot);

static __inline__ void SetBit(int *a, int bit)
{
    int *pw = &a[bit / 32];
    int m = 1 << bit;
    *pw |= m;
}

void func_001C5C18(struct SLOTS *s, struct OBJ *o)
{
    if (o->slot < 0) {
        unsigned int i;
        unsigned int w, bit;
        int n, slot;
        for (i = 0; ; i++) {
            if (i >= 8)
                return;
            w = s->free[i];
            if (!w)
                continue;
            bit = -w & w;
            s->free[i] = w & ~bit;
            n = i * 32;
            if (bit & 0xAAAAAAAA) n += 1;
            if (bit & 0xCCCCCCCC) n += 2;
            if (bit & 0xF0F0F0F0) n += 4;
            if (bit & 0xFF00FF00) n += 8;
            if (bit & 0xFFFF0000U) slot = n + 16; else slot = n;
            break;
        }
        s->objects[slot] = o;
        o->slot = slot;
    }
    if (s->disabled)
        return;
    if (o->x14C)
        return;
    if (!o->xD0 || o->x150 || !s->root)
        SetBit(s->pending, o->slot);
    else
        func_001C5A98(s, s->root, *(qword *)(o->vt[36].pfn((char *)o + o->vt[36].d) + 0x30), o->radius, o->slot);
}
