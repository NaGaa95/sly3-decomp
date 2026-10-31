// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int SegPacked __attribute__((mode(TI)));
typedef struct { SegPacked row[4]; } SegMatrix;
struct SegMethod { short delta, reserved; SegMatrix *(*function)(void *); };
struct SegTable { unsigned char prefix[0x120]; struct SegMethod frame; };
struct SegShape {
    unsigned char prefix0[0xC];
    struct SegTable *table;
    unsigned char gap10[0xD8 - 0x10];
    int count;
    unsigned char gapDC[0xE4 - 0xDC];
    SegPacked *points;
};
int func_001E6830(void *shape, SegPacked from, SegPacked to, int mode, void *hit);
int func_001E6BF0(void *shape, SegPacked point);

static inline SegPacked seg_transform(SegPacked point, SegPacked r0, SegPacked r1, SegPacked r2, SegPacked r3)
{
    SegPacked result;
    __asm__("vmulax.xyz $ACC,%1,%2x\n\tvmadday.xyz $ACC,%3,%2y\n\tvmaddaz.xyz $ACC,%4,%2z\n\tvmaddw.xyz %0,%5,$vf0w"
            : "=j"(result) : "j"(r0), "j"(point), "j"(r1), "j"(r2), "j"(r3));
    return result;
}

int func_001E7908(struct SegShape *self, struct SegShape *other)
{
    SegMatrix matrix;
    unsigned char hit[0x60];
    SegPacked second;
    SegPacked first;
    int i = 1;
    {
        SegMatrix *rows = self->table->frame.function((char *)self + self->table->frame.delta);
        matrix = *rows;
        first = seg_transform(self->points[0], matrix.row[0], matrix.row[1], matrix.row[2], matrix.row[3]);
    }
    if (i < self->count) {
        do {
            second = seg_transform(self->points[i], matrix.row[0], matrix.row[1], matrix.row[2], matrix.row[3]);
            if (func_001E6830(other, first, second, 1, hit))
                break;
            first = second;
            i++;
        } while (i < self->count);
    }
    if (i < self->count)
        return 1;
    {
        SegMatrix *rows = other->table->frame.function((char *)other + other->table->frame.delta);
        return func_001E6BF0(self, seg_transform(other->points[0], rows->row[0], rows->row[1], rows->row[2], rows->row[3])) != 0;
    }
}
