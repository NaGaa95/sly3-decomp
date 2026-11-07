// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00265000: lay out a rich text into lines (word wrap at dxWrap, back up to the last break point).
struct LINE { int ich; float dx; };
struct S {
    unsigned short *pchBase; unsigned short *pch; char pad8[0x74 - 8];
    float dxWrap; float dyMax; char pad7C[0x84 - 0x7C]; float dyLine; char pad88[4];
    float dxMax; float dyTotal; int cline; struct LINE alines[32];
};
void *memset(void *, int, unsigned int);
void func_00264B18(struct S *p, int);
unsigned short func_00264BB0(struct S *p);
float func_00264E78(struct S *p, unsigned short ch);
int func_002718D8(int ch);
int func_00271928(int ch, int chNext);
static inline float GMax(float a, float b) { return a > b ? a : b; }
void func_00265000(struct S *p)
{
    float dx = 0.0f;
    float dxSpace;
    struct LINE *pl = p->alines;
    struct LINE *plMax = &p->alines[32];
    unsigned short ch;
    int ich, ichStart;
    memset(&p->dxMax, 0, 0x10C);
    dxSpace = dx;
    func_00264B18(p, 0);
    goto start;
    for (;;) {
        if (dx != 0.0f && dxSpace != 0.0f) {
            dx -= dxSpace;
            dxSpace = 0.0f;
        }
        pl->dx = dx;
        pl++;
        p->dxMax = GMax(p->dxMax, dx);
        dx = 0.0f;
        if (pl < plMax)
            pl->ich = ichStart;
    start:
        for (;;) {
            float dxCh;
            ch = func_00264BB0(p);
            if (!ch)
                goto done;
            ich = p->pch - p->pchBase;
            dxCh = func_00264E78(p, ch);
            ichStart = ich;
            if (func_002718D8(ch)) {
                if (ch == '\n')
                    break;
                dxSpace += dxCh;
                if (dx != 0.0f)
                    dx += dxCh;
            } else {
                dx += dxCh;
                dxSpace = 0.0f;
            }
            if (p->dxWrap == 0.0f || p->dyMax < p->dyLine + p->dyLine || dx <= p->dxWrap)
                continue;
            {
                int d = -1;
                float dxPrev;
                unsigned short c;
                if ((unsigned int)p->cline >= 32)
                    goto done;
                dxPrev = dx - dxCh;
                ich--;
                dx = dxPrev;
                if (ich >= pl->ich) {
                    unsigned short cn;
                    c = p->pch[d - 1];
                    cn = p->pch[d];
                    if (c != '\n') {
                    ichStart = ich;
                    do {
                        if (func_00271928(c, cn)) {
                            dxSpace = func_002718D8(c) ? func_00264E78(p, ' ') : 0.0f;
                            p->pch += d;
                            goto newline;
                        }
                        dx -= func_00264E78(p, c);
                        ichStart--;
                        d--;
                        if (ichStart < pl->ich)
                            break;
                        c = p->pch[d - 1];
                        cn = p->pch[d];
                    } while (c != '\n');
                    }
                }
                dx = dxPrev;
                ichStart = ich;
                p->pch--;
                goto newline;
            }
        }
    newline:
        if (pl >= plMax)
            break;
    }
done:
    if (pl < plMax) {
        if (dx != 0.0f && dxSpace != 0.0f)
            dx -= dxSpace;
        pl->dx = dx;
        pl++;
        p->dxMax = GMax(p->dxMax, dx);
    }
    p->cline = pl - p->alines;
    p->dyTotal = p->cline * p->dyLine;
}
