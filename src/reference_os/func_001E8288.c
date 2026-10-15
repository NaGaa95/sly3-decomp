// Sly 2 reference: src/hand/func_001BE1E8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct DL { void *pvFirst; void *pvLast; int ibDle; };
extern struct DL D_0047A26C;
void func_0011B028(struct DL *pdl, void *pv);
void func_001E7228(void *pv);
int func_0011B0F0(struct DL *pdl);
void func_001E8288(void)
{
    while (!func_0011B0F0(&D_0047A26C)) {
        void *pv = D_0047A26C.pvFirst;
        func_0011B028(&D_0047A26C, pv);
        func_001E7228(pv);
    }
}
