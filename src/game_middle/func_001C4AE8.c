// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Walk the ring of entry lists (up to four flagged entries), then test each one's position, transformed by the
// owner's matrix, with func_00119C90 and hand the rejected ones to func_001C4CA8; remember the ring cursor and list.
typedef int qword __attribute__((mode(TI)));
struct VT { short d; short pad; void *pfn; };
struct Obj { char pad00[0xC]; struct VT *vt; char pad10[0xDC - 0x10]; int xDC; };
struct Item { char pad00[0x20]; struct Item *next; char pad24[0x2F - 0x24]; unsigned long flags : 8; };
struct M4 { qword r[4]; };
struct Spawner {
    char pad00[0x40];
    struct Obj *owner;
    int cursor;
    struct Item *item;
    int count;
    int ids[1];
};
extern char D_00475480[];
void func_001C8168(struct Spawner *self);
int func_001A9478(void *game, int a);
struct Item **func_0017DBD0(void *game, int id);
void func_0011D768(struct M4 *dst, struct M4 *src);
int func_00119C90(int owner, int mask, qword pos);
void func_001C4CA8(struct Spawner *self, struct Item *item);
static inline struct M4 *GetMatrix(struct Obj *o) { return ((struct M4 *(*)(void *))o->vt[36].pfn)((char *)o + o->vt[36].d); }
static inline qword *GetPosition(struct Obj *o) { return (qword *)((char *)((struct M4 *(*)(void *))o->vt[36].pfn)((char *)o + o->vt[36].d) + 0x30); }
// affine point transform: x*r0 + y*r1 + z*r2 + r3
static inline qword Transform(struct M4 *m, qword p)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%2,%1x\n\tvmadday.xyz $ACC,%3,%1y\n\tvmaddaz.xyz $ACC,%4,%1z\n\tvmaddw.xyz %0,%5,$vf0w"
            : "=j"(r) : "j"(p), "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(m->r[3]));
    return r;
}
void func_001C4AE8(struct Spawner *self)
{
    struct Item *found[4];
    struct M4 m;
    int tries, count, cursor, i;
    struct Item *item;
    func_001C8168(self);
    if (func_001A9478(D_00475480, -1))
        return;
    tries = 0;
    item = self->item;
    count = 0;
    cursor = self->cursor;
    if (self->count > 0) {
        do {
            while (item) {
                if (item->flags & 1) {
                    found[count++] = item;
                    if ((unsigned int)count >= 4) {
                        item = item->next;
                        goto collected;
                    }
                }
                item = item->next;
            }
            tries++;
            cursor = (cursor + 1) % self->count;
            item = *func_0017DBD0(D_00475480, self->ids[cursor]);
        } while (tries < self->count);
    }
collected:
    func_0011D768(&m, GetMatrix(self->owner));
    {
        int owner = self->owner->xDC;
        for (i = 0; i < count; i++) {
            if (!func_00119C90(owner, 0x7FFFFFFF, Transform(&m, *GetPosition(found[i]))))
                func_001C4CA8(self, found[i]);
        }
    }
    self->item = item;
    self->cursor = cursor;
}
