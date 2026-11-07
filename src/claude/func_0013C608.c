// SLY3_CFLAGS: -Os -G0
// SLY3_ASM: gnu-reorder-db
// (A16 draft; A70: the missing tool was GNU as reorder-mode, which keeps the target's in-loop beqz/nop + bnel)
struct N { int f0; struct N *pnext; int f8; int key; };
struct L { char pad[0x64]; struct N *phead; };
struct K { char pad[0x60]; int key; };
struct N *func_0013C608(void *unused, struct L *pl, struct K *pk) {
    struct N *pn = pl->phead;
    register int key __asm__("$4") = pk->key; /* pin: key lives in a0 as in the target */
    if (pn) {
        if (pn->key == key) {
            pl->phead = pn->pnext;
        } else {
            struct N **ppn = &pn->pnext;
            for (;;) {
                pn = pn->pnext;
                if (!pn) break;
                if (pn->key == key) { *ppn = pn->pnext; break; }
                ppn = &pn->pnext;
            }
        }
    }
    return pn;
}
