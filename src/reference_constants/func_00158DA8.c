// Reference algorithm: src/hand/func_00145D00.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
void func_00238978(void *p);
void func_001591E8(void *p, int n);
void func_00158DA8(char *p)
{
    struct O *o;
    struct VTE *e;
    func_00238978(p);
    func_001591E8(p, 0);
    o = *(struct O **)(p + 0x10);
    e = &o->vt[108];
    ((void (*)(void *, int, int, int, int))e->pfn)((char *)o + e->d, 4, *(int *)(p + 0x38), 4, *(int *)(p + 0x38));
    *(int *)(*(char **)(p + 0x10) + 0x11B8) |= 1;
}
