// Reference algorithm: src/hand/func_001D7B88.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct MSG { int cb; int nKind; };
typedef struct BIS BIS;
typedef struct { int c; void *pv; char ht[1]; } OBJ;
extern char D_0036B118[];
extern struct G D_00468D30;
int func_00119048(BIS *);
void func_00118DA0(BIS *, int, void *);
void func_00119790(BIS *, char **, void *, int);
void func_0021CA00(void *, int);
void func_0021CA90(void *, char *, int);
void *func_001D2470(struct MSG *);
void func_0021C0F0(OBJ *, struct G *);
void func_0021BFF8(OBJ *p, BIS *pbis)
{
    struct MSG msg;
    char *pchz;
    int i;
    int n;
    int c;
    n = func_00119048(pbis);
    func_0021CA00(p->ht, n);
    for (i = 0; i < n; i++) {
        int v = func_00119048(pbis);
        func_00119790(pbis, &pchz, D_0036B118, 0x37);
        func_0021CA90(p->ht, pchz, v);
    }
    c = func_00119048(pbis);
    p->c = c;
    msg.cb = c * 10;
    msg.nKind = 0x10;
    p->pv = func_001D2470(&msg);
    func_00118DA0(pbis, c * 10, p->pv);
    func_0021C0F0(p, &D_00468D30);
}
