// Reference algorithm: src/hand/func_00129D58.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short tag; short pad; union { int n; float g; } value; } CRef; CRef *func_0012AF00(CRef *,CRef *); CRef *func_0012BAE8(CRef *p,CRef *source) { if (source->tag == 0x14) func_0012AF00(p, source); else { float value = (float)source->value.n; p->tag = 0x14; p->value.g = value; } return p; }
