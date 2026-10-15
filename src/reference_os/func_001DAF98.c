// Sly 2 reference: src/hand/func_001B2DB8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct S { int x0; int x4; int x8; int xC; int x10; int x14; int x18; int x1C; char pad[0xC]; int x2C; };
struct REQ { int a; int b; int c; int d; };
void func_00293920(int n);
int func_00293A60(struct REQ *r, int n);
int func_00293A40(int h);
void func_00291C48(int b, int x);
int func_001DAF98(struct S *p, int b, int c)
{
    struct REQ req;
    int off, h, n;
    off = (p->x4 == 0x10) ? 0 : p->x1C;
    req.a = c;
    req.b = p->x14 + off;
    req.c = b;
    req.d = 0;
    func_00293920(0);
    h = func_00293A60(&req, 1);
    while (func_00293A40(h) >= 0) ;
    if (p->x4 == 0x10) {
        int col, row;
        n = p->x2C / 1024;
        col = n % p->xC;
        row = (n / p->xC) % 4;
        func_00291C48(b, (row << 10) + (col << 12));
    }
    return b;
}
