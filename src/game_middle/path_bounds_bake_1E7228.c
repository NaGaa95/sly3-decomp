// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int BakePacked __attribute__((mode(TI)));
typedef struct { BakePacked row[4]; } BakeMatrix;
typedef union { BakePacked raw; float lane[4]; } BakeVector;
struct BakeMethod { short delta, reserved; BakeMatrix *(*function)(void *); };
struct BakeTable { unsigned char prefix[0x120]; struct BakeMethod frame; };
struct BakeSelf {
    unsigned char prefix0[0xC];
    struct BakeTable *table;
    unsigned char gap10[0xD8 - 0x10];
    int count;
    unsigned char gapDC[0xE4 - 0xDC];
    BakePacked *points;
    unsigned char gapE8[0x190 - 0xE8];
    BakeVector minimum;
    BakeVector maximum;
};
struct BakeAllocation { int bytes, alignment; };
extern float D_00324BC0;
extern float D_00324BC4;
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
void *func_001D25B0(struct BakeAllocation *request);
void *func_001ED678(BakePacked position, int option);
void func_001EE448(void *found, struct BakeSelf *self);

static inline struct BakeAllocation *bake_request(struct BakeAllocation *request, int bytes, int alignment)
{
    request->bytes = bytes;
    request->alignment = alignment;
    return request;
}
static inline BakePacked bake_transform(BakePacked point, BakePacked r0, BakePacked r1, BakePacked r2, BakePacked r3)
{
    BakePacked result;
    __asm__("vmulax.xyz $ACC,%1,%2x\n\tvmadday.xyz $ACC,%3,%2y\n\tvmaddaz.xyz $ACC,%4,%2z\n\tvmaddw.xyz %0,%5,$vf0w"
            : "=j"(result) : "j"(r0), "j"(point), "j"(r1), "j"(r2), "j"(r3));
    return result;
}
static inline BakePacked bake_minimum(BakePacked a, BakePacked b)
{
    BakePacked result;
    __asm__("vmini.xyz %0,%1,%2" : "=j"(result) : "j"(a), "j"(b));
    return result;
}
static inline BakePacked bake_maximum(BakePacked a, BakePacked b)
{
    BakePacked result;
    __asm__("vmax.xyz %0,%1,%2" : "=j"(result) : "j"(a), "j"(b));
    return result;
}

void func_001E7228(struct BakeSelf *self)
{
    unsigned char frame[16];
    struct BakeAllocation allocation;
    BakePacked *out;
    BakeMatrix matrix;
    BakePacked result;
    BakeMatrix *rows;
    void *found;
    int i;
    func_001D2770(frame);
    out = func_001D25B0(bake_request(&allocation, self->count * 16 - 1, 16));
    rows = self->table->frame.function((char *)self + self->table->frame.delta);
    matrix = *rows;
    result = bake_transform(self->points[0], matrix.row[0], matrix.row[1], matrix.row[2], matrix.row[3]);
    self->minimum.raw = result;
    self->maximum.raw = result;
    out[0] = result;
    out[self->count - 1] = self->minimum.raw;
    for (i = 1; i < self->count - 1; i++) {
        BakePacked point = bake_transform(self->points[i], matrix.row[0], matrix.row[1], matrix.row[2], matrix.row[3]);
        self->minimum.raw = bake_minimum(self->minimum.raw, point);
        self->maximum.raw = bake_maximum(self->maximum.raw, point);
        out[i] = point;
    }
    self->minimum.lane[2] = D_00324BC0;
    self->maximum.lane[2] = D_00324BC4;
    rows = self->table->frame.function((char *)self + self->table->frame.delta);
    found = func_001ED678(rows->row[3], 0);
    if (!found) {
        func_001D2798(frame, 2);
        return;
    }
    func_001EE448(found, self);
    func_001D2798(frame, 2);
}
