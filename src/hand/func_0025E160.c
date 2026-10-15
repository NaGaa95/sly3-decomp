// Return the indexed global word, using -1 as the absent index.
// Reference algorithm: src/hand/func_001FD0C0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern int D_002EDF10[];
int func_0025E160(int n) { if (n == -1) return -1; return D_002EDF10[n]; }
