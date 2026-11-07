// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct RGBA { unsigned char r, g, b, a; };
struct S {
    int x0; unsigned short *pch; int x8; int xC; int x10; struct RGBA c14; struct RGBA c18; struct RGBA c1C;
    char pad[0x60 - 0x20]; int n60;
};
int func_00180850(int ch);
void func_00264F10(struct S *);
unsigned short func_00264BB0(struct S *p)
{
    int done = 0;
    p->n60 = 0;
    do {
        unsigned short *pc = p->pch;
        switch (*pc) {
        case '&':
            if (pc[1] == '&') {
                p->pch = pc + 1;
                done = 1;
            } else if (pc[1] == '.') {
                p->pch += 2;
                p->x8 = p->xC;
                p->c14 = p->c18;
                p->n60 = 1;
                func_00264F10(p);
            } else {
                int r = func_00180850(pc[1]);
                if (r == 1) {
                    p->x8 = p->x10;
                    p->pch += 2;
                    p->c14 = p->c1C;
                    p->n60 = r;
                    func_00264F10(p);
                } else {
                    done = 1;
                }
            }
            break;
        default:
            done = 1;
            break;
        }
    } while (!done);
    { struct { unsigned short c; } t; t.c = *p->pch++; return t.c; }
}
