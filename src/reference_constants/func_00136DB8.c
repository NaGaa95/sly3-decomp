// Reference algorithm: src/hand/func_0012FDE8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CB { int a; int b; } CB;
typedef struct E { float x; float y; int n; } E;
typedef struct T { char pad[0xA0]; E *pe; } T;
E *func_001D2470(CB *pcb);
void func_00136DB8(T *t, int n, float x, float y)
{
    CB cb;
    E *pe;
    cb.a = 0xC;
    cb.b = 0x10;
    pe = func_001D2470(&cb);
    t->pe = pe;
    pe->x = x;
    pe->y = y;
    pe->n = n;
}
