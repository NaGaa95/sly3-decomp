// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Obj { qword pos; qword up; unsigned char pad20[0x4C - 0x20]; int health; unsigned char pad50[8]; float spin; float wobble; };
struct Event { unsigned char pad0[0x14]; int kind; unsigned char pad18[8]; int sound; int damage; unsigned char pad28[8]; qword where; qword dir; int flags; };
struct Self { unsigned char pad0[0x198]; void *effects; };
extern qword D_00317550;
extern qword D_00317560;
extern float D_00322080;
struct Obj *func_0019F2D0(struct Self *self, qword pos);
void func_001F4DD8(struct Self *self, int kind, int sound, float g);
float func_0011E940(float lo, float hi);
void func_0019E8F0(struct Self *self, struct Obj *obj, int how);
void func_00179E58(void *effects, int kind, int a, qword b, qword c, float x, float y);
static inline qword Cross3(qword a, qword b)
{
    qword result;
    __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(result) : "j"(a), "j"(b));
    return result;
}
static inline qword Dot3(qword a, qword b)
{
    qword product, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "=j"(product), "=j"(one) : "j"(a), "j"(b));
    return product;
}
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
int func_0019F370(struct Self *self, struct Event *ev)
{
    struct Obj *obj;
    if (!(ev->flags & 2)) goto fail;
    __asm__ __volatile__("" ::: "memory"); /* zero-instruction barrier: reload_cse keeps the a0 = self copy */
    obj = func_0019F2D0(self, ev->where);
    if (!obj) goto fail;
    func_001F4DD8(self, ev->kind, ev->sound, D_00322080);
    obj->health -= ev->damage;
    if (obj->health > 0) {
        obj->spin = GetX(Dot3(ev->dir, Cross3(D_00317550, obj->up))) * 0.25f;
        obj->wobble = func_0011E940(-15.0f, 15.0f);
        func_0019E8F0(self, obj, 1);
    } else {
        if (self->effects) {
            func_00179E58(self->effects, 4, 0, D_00317560, obj->pos, 0.0f, 0.0f);
        }
        func_0019E8F0(self, obj, 2);
    }
    return 1;
fail:
    return 0;
}
