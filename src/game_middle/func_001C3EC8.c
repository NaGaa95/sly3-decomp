// SLY3_CFLAGS: -Os -G0
// SLY3_AS: gnu-2.9
// Predicate on an input mask: for 0x2000 / 0x4000 decide from the owner's three state words (nested switches),
// for every other mask ask the owner's virtual method (vtable slot 81) and return whether it answered non-zero.
// Same routine as Sly 2 func_001A2230 (state offsets differ; Sly 3 has no early-out and a virtual call instead).
struct VT { short d; short pad; int (*pfn)(void *); };
struct Obj { char pad00[0xC]; struct VT *vt; };
struct Part {
    char pad000[0x33C]; int subState;
    char pad340[0x508 - 0x340]; int mode;
    char pad50C[0xE44 - 0x50C]; int state;
};
struct Holder { struct Part *part; };
int func_001C3EC8(struct Holder *self, int mask)
{
    if (mask == 0x2000 || mask == 0x4000) {
        switch (self->part->state) {
        case 3: case 5: case 11: case 12:
            return 1;
        case -1:
            switch (self->part->mode) {
            default:
            case 0: case 3: case 4: case 7: case 8:
                return 1;
            case -1:
                switch (self->part->subState) {
                case -1:
                    break;
                case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
                    if (mask == 0x4000) return 1;
                    break;
                }
            case 1: case 2: case 5: case 6: case 9:
                return 0;
            }
        }
        return 0;
    }
    {
        struct Obj *o = (struct Obj *)self->part;
        return o->vt[81].pfn((char *)o + o->vt[81].d) != 0;
    }
}
