// Reference algorithm: src/hand/func_00120CC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short tag; short padding; int value; } CRef; CRef *func_0012AF00(CRef *,CRef *); CRef *func_00122808(CRef *p, void *unused, CRef *reference) { func_0012AF00(p, (CRef *)reference->value); return p; }
