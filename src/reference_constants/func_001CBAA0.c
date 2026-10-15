// Reference algorithm: src/hand/func_002296C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct N { char unknown_prefix[0xAC]; struct N *next; };
void func_0011E1F0(void *pool, struct N *n);
void func_001CBAA0(char *p, struct N *n)
{
    while (n) {
        struct N *next = n->next;
        func_0011E1F0(p + 0x44DC, n);
        n = next;
    }
}
