// Lazily construct and initialize a resource, clear flag 0x40 and set flags 0xC in immediate or indirect storage; reactivate an existing resource when requested.
// Reference algorithm: src/hand/func_001E7840.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct P { char pad[0x3C]; int fl; char pad2[0x16C - 0x40]; void *px; };
void *func_001D27F0(int cb);
void *func_0022FDE0(void *pv, struct P *p);
void func_0022DB08(struct P *p);
void func_001C9118(struct P *p, int n);
void *func_0022F450(struct P *p, int f)
{
    if (!p->px) {
        p->px = func_0022FDE0(func_001D27F0(0x90), p);
        func_0022DB08(p);
        func_001C9118(p, 0);
        { int v = p->fl; if ((v ^ 1) & 1) *(int *)v &= ~0x40; else p->fl = v & ~0x40; }
        { int v = p->fl; if ((v ^ 1) & 1) *(int *)v |= 0xC; else p->fl = v | 0xC; }
    } else if (f == 1) {
        func_001C9118(p, 0);
        { int v = p->fl; if ((v ^ 1) & 1) *(int *)v |= 0x4; else p->fl = v | 0x4; }
    }
    return p->px;
}
