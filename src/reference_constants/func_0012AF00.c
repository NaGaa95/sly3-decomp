// Reference algorithm: src/hand/func_001320C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CRef { unsigned short tag,reserved; int value; }; void func_0012BB38(struct CRef *); struct CRef *func_0012AF00(struct CRef *p,const struct CRef *source) { p->tag=source->tag; p->value=source->value; func_0012BB38(p); return p; }
