// SLY3_CFLAGS: -Os -G0
// Port of Sly 2 func_002314D0 (src/hand/func_002314D0.c).
typedef int qword __attribute__((mode(TI)));
typedef struct { float m[16]; } __attribute__((aligned(16))) M4;
typedef struct X { char pad[0x40]; void *x40; } X;
extern qword D_00317560;
M4 func_0028BAD0(void *, int);

static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}

qword func_00290160(X *p)
{
    if (!p->x40) return D_00317560;
    {
        M4 m;
        {
            M4 t = func_0028BAD0(p->x40, 0);
            m = t;
        }
        {
            union { qword q; float f; } r;
            r.q = Make(m.m[6], m.m[8], m.m[1]);
            return r.q;
        }
    }
}
