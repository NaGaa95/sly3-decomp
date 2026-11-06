// SLY3_CFLAGS: -Os -G0
// Return the pointer at +0xD8.
struct Holder { char prefix[0xD8]; void *pd8; };
void *func_002412C0(struct Holder *p) { return p->pd8; }
