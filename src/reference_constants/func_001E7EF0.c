// Reference algorithm: src/hand/func_001BDE18.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct O { char pad[0x1B4]; struct DL dl; char pad2[0x1D8 - 0x1D0]; void *powner; };
extern struct DL D_0047A26C;
void func_0011AF60(struct DL *pdl, void *pv);
void func_0011B028(struct DL *pdl, void *pv);
int func_0011B0C0(struct DL *pdl, void *pv);
void func_001E73D8(void *p);
void func_001E7EF0(void *p, struct O *po)
{
    struct DL *pdl;
    *(struct O **)((char *)p + 0x1C8) = po;
    func_0011AF60(&po->dl, p);
    func_001E73D8(p);
    pdl = &D_0047A26C;
    if (func_0011B0C0(pdl, p)) func_0011B028(pdl, p);
}
