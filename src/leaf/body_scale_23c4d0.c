// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Scale the three rows of the body matrix by `s` (port of Sly 2 func_001F35F8), then refresh the second block.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { qword r[3]; } M3;
struct Body { M3 m; qword v[3]; };
struct Actor { char pad[0xD8]; struct Body *body; };
void func_00291E8C(void *d, const void *s, unsigned int cb);
void *func_00292034(void *d, int c, unsigned int cb);
int func_0011C6D0(struct Body *body, qword *v);
void func_0023C4D0(struct Actor *p, float s)
{
    struct Body *body = p->body;
    M3 m;
    U u;
    M3 r;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(s));
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r.r[0]) : "j"(u.q), "j"(body->m.r[0]));
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r.r[1]) : "j"(u.q), "j"(body->m.r[1]));
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r.r[2]) : "j"(u.q), "j"(body->m.r[2]));
    func_00291E8C(&m, &r, sizeof(M3));
    body->m = m;
    if (!func_0011C6D0(p->body, p->body->v))
        func_00292034(p->body->v, 0, 0x30);
}
