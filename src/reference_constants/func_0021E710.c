// Reference algorithm: src/hand/func_001DA350.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern struct CLOCK { float t; float dt; } D_0036BB98;
typedef struct { char pad[0x48]; int x58; } W;
typedef struct {
    char pad[0x10];
    int state;
    float t;
    int x18;
    float x1C;
    int x20;
    float x24;
    W *pw;
} OBJ;
void func_0021E980(OBJ *, int);
int func_00261BD0(W *);
int func_00260758(W *, int);
void func_0021E710(OBJ *p)
{
    if (p->pw == 0)
        return;
    switch (p->state) {
    case 0:
        break;
    case 1:
        if (p->pw->x58 == 2)
            func_0021E980(p, 2);
        break;
    case 2:
        if (p->x20 != -1) {
            func_0021E980(p, 4);
        } else if (p->x1C == 0.0f) {
            func_0021E980(p, 3);
        } else if (0.0f < p->x1C) {
            if (p->pw && !func_00261BD0(p->pw))
                p->t += D_0036BB98.dt;
        }
        break;
    case 3:
        if (p->pw->x58 < 2)
            func_0021E980(p, 0);
        break;
    case 4:
        if (func_00260758(p->pw, 0x379))
            break;
        if (p->x20 == -1)
            func_0021E980(p, 0);
        else
            func_0021E980(p, 2);
        break;
    }
}
