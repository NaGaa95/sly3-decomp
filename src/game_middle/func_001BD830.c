// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math
// Is the requested action available for the actor in its current mode? (same routine as Sly 2 func_0019C8D0)
struct O { char pad[0x13E0]; int x13E0; };
struct S { struct O *p; int x4; int pad[5]; int x1C; };
int func_001BD830(struct S *p, int k)
{
    if (p->x4 == 16)
        return 0;
    switch (k) {
    case 23:
        if (p->x4 >= 16) goto L;
        if (p->x4 < 14) goto L;
        return 0;
    default:
        return 0;
    case 3:
        {
            int r = 0;
            if (p->x1C == 0x12 && p->p->x13E0)
                r = 1;
            return r;
        }
    case 2: case 4: case 17: case 27:
    L:
        switch (p->x1C) {
        case 8: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
        case 17: case 18: case 19: case 20: case 21: case 22:
            return 0;
        }
        return 1;
    }
}
