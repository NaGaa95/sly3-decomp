// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: /home/claude/decomp src/hand/func_0014FE58.c (position + 150 * up when flag 0x33 set).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct LO { char pad[0xC]; struct VEntry *table; };
struct X { char pad[0x20]; struct LO *po; };
extern qword D_00317550;
int func_0013B500(void *p, int k);
qword func_00169FF0(struct X *p)
{
    U s;
    U pos;
    pos.q = *(qword *)((char *)p->po->table[36].get((char *)p->po + p->po->table[36].delta) + 0x30);
    if (func_0013B500(p->po, 0x33)) {
        qword rs;
        register qword rp __asm__("vf3") = pos.q; /* single pin: VU allocation order */
        qword rd = D_00317550;
        __asm__("qmtc2.ni %1, %0" : "=j"(rs) : "r"(150.0f));
        s.q = rs;
        __asm__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %2, %1x" : "+j"(rp) : "j"(rs), "j"(rd));
        pos.q = rp;
    }
    return pos.q;
}
