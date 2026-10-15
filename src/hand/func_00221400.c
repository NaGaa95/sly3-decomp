// When the controller is in the required mode, resolve each descriptor's selected and unselected event handles and update the type-specific secondary handle.
// Reference algorithm: src/hand/func_001DD1F8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct { char pad[0x48]; int x58; } W;
typedef struct { void *p; int a; int b; } ENT;
typedef struct {
    char pad[0x34];
    W *pw;
    char pad28[0x40 - 0x28];
    int kind;
    char pad44[4];
    int c;
    ENT ae[17];
    int sel;
} OBJ;
void func_00262B60(W *, int, int *);
int func_00187CD0(void *);
int func_00188A38(void *);
void func_00221400(OBJ *p)
{
    int i;
    if (p->pw->x58 != 2)
        return;
    for (i = 0; i < p->c; i++) {
        int f;
        ENT *pe = &p->ae[i];
        func_00262B60(p->pw, i == p->sel ? i + 0x58B : i + 0x577, &pe->a);
        f = 0;
        switch (p->kind) {
        case 0:
            f = func_00187CD0(pe->p);
            break;
        case 1:
            f = func_00188A38(pe->p);
            break;
        }
        func_00262B60(p->pw, f ? i + 0x595 : -1, &pe->b);
    }
}
