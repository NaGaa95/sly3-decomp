// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Method { short delta, reserved; void *call; };
struct Obj { unsigned char pad00[0xC]; struct Method *methods; unsigned char pad10[0x2F - 0x10]; unsigned long flags : 8; };
struct E { struct Obj *obj; float t; };
extern float g_clock;

void func_00145F70(char *p, qword v)
{
    struct E *best = 0;
    float tmin = 3.402823466e+38f;
    struct E *ae = (struct E *)(p + 0x360);
    unsigned int i;
    for (i = 0; i < 4; i++) {
        struct E *e = &ae[i];
        if (e->obj) {
            if (e->obj->flags & 1) {
                if (e->t < tmin) {
                    best = e;
                    tmin = e->t;
                }
            } else {
                best = e;
                break;
            }
        }
    }
    if (best) {
        struct Obj *o = best->obj;
        ((void (*)(void *))o->methods[8].call)((char *)o + o->methods[8].delta);
        o = best->obj;
        ((void (*)(void *, qword))o->methods[34].call)((char *)o + o->methods[34].delta, v);
        best->t = g_clock;
    }
}
