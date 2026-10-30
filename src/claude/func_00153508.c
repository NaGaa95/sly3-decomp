// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct Slot { int a; int b; void *object; char pad[0x34]; };
struct Q { char pad[0x40]; qword v; struct Slot *slots; };
int func_0013B500(void *object, int kind);
int func_00156700(void *p);
void func_002448F8(void *p, void *a, struct Q *q, void *b, int n);

void func_00153508(void *p, void *a, struct Q *q, void *b, int n)
{
    qword saved = q->v;
    struct Slot *slot = &q->slots[1 - n];
    if (slot->object && func_0013B500(slot->object, 0x33) && func_00156700(p)) {
        U u;
        qword r;
        __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(0.01f));
        __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(u.q), "j"(saved));
        q->v = r;
    }
    func_002448F8(p, a, q, b, n);
    q->v = saved;
}
