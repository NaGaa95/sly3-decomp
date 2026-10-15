// Reference algorithm: src/hand/func_001D84B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct { char ab[0x6808]; } BIG;
typedef struct {
    short ch;
    signed char x2;
    unsigned char x3;
    unsigned short x4;
    unsigned short iChild;
    unsigned short iSibling;
} ENT;
typedef struct { int c; ENT *ae; char ht[1]; } OBJ;
extern BIG D_00468D30;
extern char D_00325F30[];
int func_0021CB20(void *, char *);
static inline int NFind(OBJ *ph, char *pch) { return func_0021CB20(ph->ht, pch); }
void func_0021C718(OBJ *p, BIG *pbig)
{
    int n;
    int i;
    *pbig = D_00468D30;
    n = NFind(p, D_00325F30);
    if (n == -1)
        return;
    for (i = 0; i < p->c; i++) {
        ENT *pe = &p->ae[i];
        if (pe->ch == n)
            pbig->ab[pe->x4] = 1;
    }
}
