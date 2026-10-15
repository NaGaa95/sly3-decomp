// Reference algorithm: src/hand/func_00210BE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct { int stringId; const unsigned short *text; } ENT;
typedef struct { int c; ENT *a; int x8; int xC; } TBL;
typedef struct { int a[4]; } ALLOC;
extern struct G { char pad[0x4E54]; int f; } D_00475480;
extern ALLOC *func_00117DD0(ALLOC *, int, int);
extern const unsigned short *func_00150630(struct G *, int);
extern int func_00271700(const unsigned short *);
extern unsigned short *func_00117C60(ALLOC *, const unsigned short *, int);

void func_0025E7B0(TBL *p)
{
    ALLOC al;
    int i;
    if (D_00475480.f == 0)
        return;
    func_00117DD0(&al, p->x8, p->xC);
    for (i = 0; i < p->c; i++) {
        ENT *e = &p->a[i];
        e->text = func_00150630(&D_00475480, e->stringId);
        if (func_00271700(e->text))
            e->text = func_00117C60(&al, e->text, 7);
        else
            e->text = 0;
    }
}
