// SLY3_CFLAGS: -Os -G0
struct M { char pad[0x6c]; int f6c; int f70; void *f74; };
struct S { char pad[0x50c]; int f50c; char pad2[0x1154 - 0x510]; float f1154; char pad3[0x1520 - 0x1158]; int f1520; };
extern float D_0036BB98;
extern char D_00341EE0[]; /* 0x00342C80 has no symbol yet: addressed as D_00341EE0 + 0xDA0 */
void func_00153D40(struct S *, struct M *);
void func_0013EC70(struct S *p, struct M *m) {
    int s = p->f1520;
    if (s != 0 && s != 0x12 && s != 0xb && p->f50c)
        p->f1154 = D_0036BB98;
    func_00153D40(p, m);
    m->f70 = 4;
    m->f74 = D_00341EE0 + 0xDA0;
    switch (p->f1520) {
    case 5: case 6: case 7:
        m->f6c |= 1;
        break;
    }
}
