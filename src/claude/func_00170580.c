// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of Sly 2 src/hand/func_001541D8.c (offsets moved, extra flag-0x37 test, guarded checks, new k=2 path).
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct SO { char pad[0xC]; struct VTE *vt; char pad1[0x260 - 0x10]; qword pos; char pad2[0x1280 - 0x270]; int x1280; char pad3[0x15F8 - 0x1284]; int x15F8; };
struct L { int x0; struct L *pNext; int x8; struct SO *pso; };
struct C2 { char pad[0x64]; struct L *pl; };
struct C { char pad[0xDC]; struct C2 *pc2; };
struct H { void *p0; };
struct T { char pad[0x14]; struct H *ph; char pad1[0xD0 - 0x18]; struct C *pc; char pad2[0x3C8 - 0xD4]; void *x3C8; void *x3CC; int x3D0; int x3D4; int x3D8; };
struct W { char pad[0xDC]; void *xDC; char pad1[0x120 - 0xE0]; struct W *pNext; };
struct BUF { char a[0x180]; };
extern char D_00475480[];
extern struct W *D_00479B8C;
void *func_001F4AD0(void *p, int n);
int func_001C8610(struct SO *p);
int func_0013B500(void *p, int k);
int func_001A95D0(void *p, int n);
qword func_0016FD78(struct T *p);
qword func_001C9428(int z, struct W *pw, qword v);
int func_00119BE8(void *p, int mask, qword a, qword b, int n, struct BUF *pbuf);
int func_0027F258(void *p, qword v);
int func_00170BC8(struct T *p, struct SO *pso);
int func_00170A50(struct T *p, struct SO *pso);
int func_002544E0(void *p, struct SO *pso);
#define VCALL(o, i) ((o)->vt[i].pfn((char *)(o) + (o)->vt[i].d))
#define GETPOS(o) (*(qword *)((char *)VCALL(o, 36) + 0x30))
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }

int func_00170580(struct T *p, struct SO *pso, int k)
{
    struct BUF buf;
    qword v;
    struct W *pw;
    void *pme = func_001F4AD0(D_00475480, 0);
    if (!pso) { k = 0; goto done; }
    if (!func_001C8610(pso)) { k = 0; goto done; }
    if (func_0013B500(pso, 0x31) && (int)VCALL(pso, 81) == 2) { k = 0; goto done; }
    if (func_0013B500(pso, 0x33) && pme && func_0013B500(pme, 0x45)) { k = 0; goto done; }
    if (func_001A95D0(D_00475480, -1)) { k = 0; goto done; }
    if (p->x3D4) { k = 0; goto done; }
    if (func_0013B500(pso, 0x33) && pso->x1280) { k = 0; goto done; }
    if (func_0013B500(pso, 0x37) && pso->x15F8) { k = 0; goto done; }
    if (p->x3D0) { k = 1; goto done; }
    if (func_0013B500(pso, 0x32))
        v = Add(GETPOS(pso), pso->pos);
    else
        v = GETPOS(pso);
    for (pw = D_00479B8C; pw; pw = pw->pNext) {
        qword a = func_001C9428(0, pw, func_0016FD78(p));
        qword b = func_001C9428(0, pw, v);
        if (func_00119BE8(pw->xDC, 0x7FFFFFFF, a, b, 4, &buf) > 0) { k = 0; goto done; }
    }
    switch (k) {
    case 0:
        if (p->pc && p->pc->pc2) {
            struct L *pl;
            for (pl = p->pc->pc2->pl; pl; pl = pl->pNext) {
                if (pl->pso == pso) {
                    if (pl->x0) { k = 1; goto done; }
                    break;
                }
            }
        }
        if (p->x3C8 && !func_0027F258(p->x3C8, v)) { k = 0; goto done; }
        if (p->x3CC && !func_0027F258(p->x3CC, v)) { k = 0; goto done; }
        if (!(p->x3D8 & 1) && func_00170BC8(p, pso)) { k = 0; goto done; }
        if (p->x3D8 & 2) { k = 1; goto done; }
        { k = !func_00170A50(p, pso); goto done; }
    case 1:
        if (p->x3CC && !func_0027F258(p->x3CC, v)) { k = 0; goto done; }
        if (p->x3C8 && !func_0027F258(p->x3C8, v)) {
            k = 0;
            if (func_0013B500(p->ph->p0, 0x3A))
                k = func_002544E0(p->ph->p0, pso) == 2 ? 2 : 0;
            goto done;
        }
        break;
    case 2:
        if (p->x3CC && !func_0027F258(p->x3CC, v)) { k = 0; goto done; }
        if (p->x3C8 && func_0027F258(p->x3C8, v)) {
            if (p->x3D8 & 2) { k = 1; goto done; }
            if (func_00170A50(p, pso)) return k;
            k = 1;
            goto done;
        }
        break;
    default:
        goto done;
    }
    if ((p->x3D8 & 8) && func_00170A50(p, pso)) k = 0;
done:
    return k;
}
