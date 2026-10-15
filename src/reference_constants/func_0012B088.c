// Reference algorithm: src/hand/func_00129398.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); struct Value { qword value; int references; }; struct CRef { unsigned short tag,reserved; struct Value *value; }; extern char D_004D2F58[]; struct Value *func_0011E118(void *); struct CRef *func_0012B088(struct CRef *p,const qword *source) { struct Value *value; p->tag=26; value=func_0011E118(D_004D2F58); value->references=0; p->value=value; ++value->references; p->value->value=*source; return p; }
