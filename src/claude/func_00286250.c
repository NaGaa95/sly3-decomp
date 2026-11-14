// SLY3_CFLAGS: -Os -G0
// func_00286250: state-machine step loop (states 1-3), re-run while the state changes.
// The target's 'bltz k / bne k,1' left subtree is a merged 'case 0: case 1:' range node whose body re-tests k == 1.
struct Q { char pad[0x18]; int x18; };
struct S { char pad[0x134]; struct Q *x134; char pad2[0x1A0 - 0x138]; int state; float t1A4; char pad3[0x2C8 - 0x1A8]; void *x2C8; };
extern struct CLOCK { float t; } g_clock;
void func_00286B00(struct S *p, int state);
int func_00260738(void *p);
void func_00286250(struct S *p)
{
    int k;
    do {
        float dt = g_clock.t - p->t1A4;
        k = p->state;
        switch (k) {
        case 0:
        case 1:
            if (k == 1 && (p->x134->x18 & 0x80))
                func_00286B00(p, 2);
            break;
        case 2:
            if (!(p->x134->x18 & 0x80))
                func_00286B00(p, 1);
            else if (dt > 1.5f)
                func_00286B00(p, 3);
            break;
        case 3:
            if (!p->x2C8 || func_00260738(p->x2C8))
                func_00286B00(p, 1);
            break;
        default:
            break;
        }
    } while (p->state != k);
}
