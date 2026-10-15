// Reference algorithm: src/hand/func_001BC198.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct S { char pad[0x1C8]; void *powner; };
extern struct DL D_0047A26C;
void func_001C7938(struct S *p);
void func_001E7410(void *p);
void func_0011B028(struct DL *pdl, void *pv);
int func_0011B0C0(struct DL *pdl, void *pv);
void func_001E73D8(void *p);
void func_001E6348(struct S *p)
{
    struct DL *pdl;
    func_001C7938(p);
    if (p->powner) func_001E7410(p->powner);
    func_001E73D8(p);
    pdl = &D_0047A26C;
    if (func_0011B0C0(pdl, p)) func_0011B028(pdl, p);
}
