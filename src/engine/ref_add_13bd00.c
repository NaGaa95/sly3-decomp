// SLY3_CFLAGS: -Os -G0
struct RefEntry { int id; int cref; struct RefEntry *pnext; };
struct RefOwner { int pad[2]; struct RefEntry *pfirst; };
extern char D_004798D0[];
void *func_0011E118(void *pool);
void func_0013BD00(struct RefOwner *p, int id)
{
    struct RefEntry *pe;
    for(pe = p->pfirst; pe; pe = pe->pnext) {
        if(pe->id == id) {
            pe->cref++;
            return;
        }
    }
    pe = func_0011E118(D_004798D0);
    pe->id = id;
    pe->cref = 1;
    pe->pnext = p->pfirst;
    p->pfirst = pe;
}
