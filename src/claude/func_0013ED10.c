// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the matched Sly 2 source src/hand/func_00135940.c; "a" is the dead copy of the scale the original also stores.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct VT { short d; short pad; void *pfn; };
struct P { char pad[0xC]; struct VT *pvt; char pad1[0x320 - 0x10]; char a320[0x500 - 0x320]; char a500[0xE40 - 0x500];
    char aE40[0x10D0 - 0xE40]; char a10D0[0x1520 - 0x10D0]; int k; char pad3[0x1820 - 0x1524]; int x1820;
    char pad4[0x183C - 0x1824]; int x183C; };
void func_0024E2B8(struct P *p);
void func_001B88E0(void *p);
void func_001B5910(void *p);
void func_001C2870(void *p);
void func_0013A9E0(void *p);
void func_00244828(struct P *p, qword v);
void func_0013ED10(struct P *p)
{
    func_0024E2B8(p);
    switch (p->k) {
    case 2: func_001B88E0(p->a320); break;
    case 3: func_001B5910(p->a500); break;
    case 4: func_001C2870(p->aE40); break;
    case 8:
    case 16:
        if (p->x1820 == 2 || p->x183C == 2 || p->x183C == 5) {
            register struct VT *vt __asm__("$2") = p->pvt; /* the one pin: vt lives in v0 */
            U a, u;
            qword v, r, q;
            qword (*pfn)(void *);
            short d;
            char *pp;
            d = vt[38].d;
            __asm__("mfc1 %0, %1" : "=r"(q) : "f"(-2.5f));
            u.q = q;
            pfn = (qword (*)(void *))vt[38].pfn;
            a.q = q;
            pp = (char *)p + d;
            v = pfn(pp);
            __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "0"(u.q), "j"(v));
            func_00244828(p, r);
        }
        break;
    case 17: func_0013A9E0(p->a10D0); break;
    }
}
