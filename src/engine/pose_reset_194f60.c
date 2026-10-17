// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct PoseObject { unsigned char prefix[0x128]; unsigned long flags; };
struct PoseEntry { float x; float y; float z; float w; unsigned char gap10[8]; };
struct PoseSelf {
    struct PoseObject *object; unsigned char gap4[0x10 - 4]; Qword zero;
    float limit; unsigned char gap24[0x44 - 0x24]; struct PoseEntry *entries;
};
extern struct { Qword m; } D_00317560;
void func_00211F18(void *object);
float func_002BE308(void *vector);
float func_002BE310(void *vector);
float func_002BE318(void *vector);
void func_00194F60(struct PoseSelf *self, int index)
{
    float limit = 1000000.0f;
    struct PoseEntry *entry;
    Qword vector;
    float x, y, z;
    func_00211F18(self->object);
    self->object->flags &= ~8UL;
    self->zero = D_00317560.m;
    self->limit = limit;
    entry = self->entries + index;
    vector = D_00317560.m;
    x = func_002BE308(&vector);
    y = func_002BE310(&vector);
    z = func_002BE318(&vector);
    entry->w = limit;
    entry->x = x;
    entry->y = y;
    entry->z = z;
}
