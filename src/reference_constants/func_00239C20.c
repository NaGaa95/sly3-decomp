// Reference algorithm: src/hand/func_001F0598.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short p; void *pfn; };
struct VT { struct VTE a[4]; };
struct Q { char pad[0x58]; char dl[1]; };
struct P { char pad[0xC]; struct VT *pvt; char pad2[0x24 - 0x10]; struct Q *pq; char pad3[0x30 - 0x28]; void *p30; };
struct DL;
extern struct DL D_00479A08;
int func_00239CC0(struct P *);
void func_00137B00(void *);
void func_0011B028(void *, void *);
void func_00239C20(struct P *p)
{
    if (!func_00239CC0(p)) {
        void *pv = p->p30;
        if (pv) {
            p->p30 = 0;
            func_00137B00(pv);
        }
        func_0011B028(p->pq->dl, p);
        func_0011B028(&D_00479A08, p);
        ((void (*)(void *, int, int, int, int, int))p->pvt->a[3].pfn)((char *)p + p->pvt->a[3].d, 3, 0, 0, 0, 0);
        ((void (*)(void *))p->pvt->a[2].pfn)((char *)p + p->pvt->a[2].d);
    }
}
