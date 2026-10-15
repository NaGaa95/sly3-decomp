// Reference algorithm: src/hand/func_001F0198.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
float func_002A3EE8(float, float);
float func_0011D4F8(float *p) { return func_002A3EE8(p[1], p[0]); }
