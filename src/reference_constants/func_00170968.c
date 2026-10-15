// Reference algorithm: src/hand/func_0017EE78.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Source { int unused; void *owner; }; int func_0025CE90(void *,struct Source *); int func_0013B868(void *); int func_00170968(void *p,struct Source *source) { if (!func_0025CE90(p, source)) return 0; return func_0013B868(source->owner) == 0x30; }
