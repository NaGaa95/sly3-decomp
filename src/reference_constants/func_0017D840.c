// Original controller lookup and fallback return the actual node pointer.
// Preserve that pointer through the consumer field60 store.
// Reference algorithm: src/hand/func_002099F0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_001F4A80(void *receiver); void func_0017D820(void *receiver,void *node); void func_0017D840(void *p,void *key) { func_0017D820(p, func_001F4A80(key)); }
