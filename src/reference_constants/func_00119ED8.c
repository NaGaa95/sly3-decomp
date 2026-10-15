// Reference algorithm: src/hand/func_0014FCC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); void func_00119ED8(qword *p,qword vector,float value) { *p = vector; ((float *)p)[3] = value; }
