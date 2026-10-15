// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct E { unsigned int h; char *s; int n; struct E *next; };
struct S { struct E *ap[0x35]; int c; struct E *ae; };
unsigned int func_0021CA40(char *s);
int func_00292F50(char *a, char *b);
int func_0021CB20(struct S *p, char *s)
{
    unsigned int h = func_0021CA40(s);
    struct E *pe;
    for (pe = p->ap[h % 0x35]; pe; pe = pe->next) {
        if (pe->h == h && func_00292F50(pe->s, s) == 0)
            return pe->n;
    }
    return -1;
}
