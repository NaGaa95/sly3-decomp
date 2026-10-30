// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Nearest object (squared XYZ distance) across all slot lists. VU helpers in the
// style of src/engine/actor_substate_update.cpp and src/hand/func_00120528.c.
typedef int qword __attribute__((mode(TI)));
struct Obj { qword pos; unsigned char pad[0x50]; struct Obj *next; };
struct Slot { struct Obj *head; unsigned char pad[0x2C]; };
struct Self { unsigned char pad0[0x1F4]; int count; unsigned char pad1F8[0x208 - 0x1F8]; struct Slot slots[1]; };
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline qword SquaredLengthXYZ(qword vector)
{
    qword product, one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\t"
        "vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "=j"(product), "=&j"(one) : "j"(vector));
    return product;
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
struct Obj *func_0019F2D0(struct Self *self, qword pos)
{
    float best = 3.402823466e+38f;
    struct Obj *nearest = 0;
    int i;
    for (i = 0; i < self->count; i++) {
        struct Obj *obj;
        for (obj = self->slots[i].head; obj; obj = obj->next) {
            float d = GetX(SquaredLengthXYZ(Sub(obj->pos, pos)));
            if (d < best) {
                best = d;
                nearest = obj;
            }
        }
    }
    return nearest;
}
