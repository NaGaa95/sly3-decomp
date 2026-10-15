// Sly 2 reference: src/hand/func_001B32B8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct S { int state; char pad[0x4C]; char x50[0x20]; int x70; int x74; int x78; int x7C; int x80; int x84; int x88; int x8C; int x90; int x94; };
int func_0014F0A0(void *a, int b, void *c);
void func_00291BE8(int a, int b, int c, int d, int e);
void func_001DB098(void *p);
void func_001DB490(struct S *p)
{
    switch (p->state) {
    case 2:
        func_0014F0A0(p->x50, p->x94, &p->x70);
        if (p->x94 == 0) {
            if (p->x74 == 0x10) func_00291BE8(p->x84, 0x1000, 0, p->x78, p->x7C);
            else func_00291BE8(p->x84, p->x88, p->x84, 0, 0);
            p->state = 3;
        }
        break;
    case 3:
        func_001DB098(&p->x70);
        func_0014F0A0(p->x50, p->x94, &p->x70);
        break;
    }
}
