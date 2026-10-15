// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[]; extern int D_00375220; const unsigned short *func_00150630(void *,int); unsigned short *func_00271730(unsigned short *,const unsigned short *); void func_001D1A70(unsigned short *p) { func_00271730(p,func_00150630(D_00475480,D_00375220)); }
