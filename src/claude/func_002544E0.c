// SLY3_CFLAGS: -Os -G0
// Classify how actor q relates to p: -1 same, 0 none/friend, 2 neutral, 3 listed foe, 1 target.
struct Q { char pad[0x1160]; struct { char pad[0x28]; int c; } *p1160; };
struct P
{
    char pad0[0x3B4];
    int c3B4;
    int a3B8[5];
    int c3CC;
    int a3D0[(0x11B8 - 0x3D0) / 4];
    int f11B8;
    int n11BC;
    int n11C0;
};
int func_00257F28(struct P *p);
int func_0013B500(struct Q *q, int cid);
int func_00251368(struct Q *q);
int func_00156D48(struct Q *q);
int func_002544E0(struct P *p, struct Q *q)
{
    int i;
    if (q == (struct Q *)p)
        return -1;
    if (func_00257F28(p)) {
        if (func_0013B500(q, 0x3A)) {
            int r = func_00251368(q);
            if (!r)
                return 2;
        }
        return 0;
    }
    for (i = 0; i < p->c3B4; i++)
        if (func_0013B500(q, p->a3B8[i]))
            return 0;
    for (i = 0; i < p->c3CC; i++)
        if (func_0013B500(q, p->a3D0[i]))
            return 3;
    if (p->f11B8)
        return 2;
    if (!func_0013B500(q, 0x33))
        return 2;
    if (func_00156D48(q) && q->p1160->c <= 0) {
        if (p->n11C0 == -1 || p->n11BC == 1)
            return 0;
        return 1;
    }
    return 2;
}
