// Reference algorithm: src/hand/func_00209A88.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); void func_0016AE90(void *); void func_0016AE40(char *p,qword first,qword second,float value) { *(qword *)(p+0x90)=first; *(qword *)(p+0xA0)=second; *(float *)(p+0xB0)=value; if(!*(int *)(p+0x50))func_0016AE90(p); *(int *)(p+0x50)=1; }
