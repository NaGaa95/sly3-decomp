// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int AlignPacked __attribute__((mode(TI)));
typedef union { AlignPacked raw; float scalar; } AlignScalarCarrier;
struct AlignMethod { short delta, reserved; void *function; };
struct AlignTable { unsigned char prefix[0x2E8]; struct AlignMethod notify; };
struct AlignObject { unsigned char prefix[0xC]; struct AlignTable *table; };
struct AlignLink { struct AlignObject *source; int word4; };
struct AlignSelf {
    struct AlignObject *object;
    unsigned char gap04[0x1C - 0x04];
    int state;
    unsigned char gap20[0x80 - 0x20];
    struct AlignLink *link;
    unsigned char gap84[0x90 - 0x84];
    AlignPacked point;
    AlignPacked normal;
    AlignPacked offset;
};
struct AlignQueryMethod { short delta, reserved; void *function; };
struct AlignQueryTable { unsigned char prefix[0x120]; struct AlignQueryMethod query; };
extern AlignPacked D_00317540;
extern AlignPacked D_00317550;
AlignPacked func_0028E910(void *source, void *destination, AlignPacked point);
void func_0011FEA8(AlignPacked normal, AlignPacked first, AlignPacked second, AlignPacked *output);

static inline AlignPacked align_scale(AlignPacked vector, float scale)
{
    AlignScalarCarrier carrier;
    AlignPacked result;
    __asm__("qmtc2.ni %1,%0" : "=j"(carrier.raw) : "r"(scale));
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(result) : "j"(vector), "j"(carrier.raw));
    return result;
}
static inline AlignPacked align_rotate(AlignPacked vector, AlignPacked row0, AlignPacked row1, AlignPacked row2)
{
    AlignPacked result;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(result) : "j"(vector), "j"(row0), "j"(row1), "j"(row2));
    return result;
}
static inline AlignPacked align_difference(AlignPacked left, AlignPacked right)
{
    AlignPacked result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(left), "j"(right));
    return result;
}

void func_001BAC20(struct AlignSelf *self)
{
    AlignPacked saved[1];
    AlignPacked mapped[1];
    AlignPacked basis[3];
    if (self->state == 0x12) {
        struct AlignQueryMethod *query = &((struct AlignQueryTable *)self->object->table)->query;
        AlignPacked normal;
        struct AlignMethod *notify;
        saved[0] = *(AlignPacked *)((char *)((void *(*)(void *))query->function)((char *)self->object + query->delta) + 0x30);
        mapped[0] = func_0028E910(self->link->source, 0, self->point);
        normal = align_scale(self->normal, -1.0f);
        basis[0] = normal;
        func_0011FEA8(normal, D_00317550, D_00317540, &basis[1]);
        mapped[0] = align_difference(mapped[0], align_rotate(self->offset, basis[0], basis[1], basis[2]));
        notify = &self->object->table->notify;
        ((void (*)(void *, int, int, AlignPacked, AlignPacked, AlignPacked))notify->function)((char *)self->object + notify->delta, 7, self->link->word4, mapped[0], D_00317540, saved[0]);
    }
}
