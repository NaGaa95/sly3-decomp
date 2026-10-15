// Original A1 is the nullable owner passed unchanged to the base initializer.
// Reference algorithm: src/hand/func_001F3868.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
void func_001FC968(void *receiver, void *owner);
void func_00170F60(void *, int);
void func_00170F60(void *, int);
void func_00170EA0(void *p, void *owner) { func_001FC968(p, owner); func_00170F60(p, -1); func_00170F60(p, 3); }
