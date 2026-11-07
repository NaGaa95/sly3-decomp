// SLY3_CFLAGS: -Os -G0
// True if p->B8 is set or some listed object has bit 0 of +0x2F set while its +0xF0 link is missing or lacks it.
struct O { char pad0[0x2F]; unsigned long f2F : 8; char pad30[0xF0 - 0x30]; struct O *pF0; };
struct P { char pad0[0x30]; int c; struct O *apo[0x21]; char padB8[0xB8 - 0xB8]; int fB8; };
int func_0024C1E8(struct P *p)
{
    int i;
    if (p->fB8)
        return 1;
    for (i = 0; i < p->c; i++) {
        struct O *po = p->apo[i];
        if (po->f2F & 1) {
            if (!po->pF0 || !(po->pF0->f2F & 1))
                return 1;
        }
    }
    return 0;
}
