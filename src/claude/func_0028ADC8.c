// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0028ADC8: expire timed entries, then dispatch per-entry state (loop condition written t > g10 so jump2 does not cross-jump the rotated entry test).
struct Q { char pad[0xC]; float gC; float g10; char pad14[0x28 - 0x14]; };
struct E { char pad[0x28]; int c; struct Q aq[1]; char pad1[0x54 - 0x2C - sizeof(struct Q)]; };
struct S { char pad[0x40]; float t40; char pad44[0x690 - 0x44]; int c; int pad694; struct E ae[1]; };
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
void func_0028AD48(struct S *p, struct E *e, int k);
void func_0028A920(struct S *p, int i, float g);
void func_0028AC30(struct S *p, int i);
void func_00289F78(struct S *p, int k);
void func_0028ADC8(struct S *p, int k)
{
    int i;
    int j;
    if (g_clock.t != p->t40) {
        for (i = 0; i < p->c; i++) {
            struct E *e = &p->ae[i];
            struct Q *q = e->aq;
            while (e->c > 0 && g_clock.t > q->g10)
                func_0028AD48(p, e, 0);
        }
        for (j = 0; j < p->c; j++) {
            struct E *e = &p->ae[j];
            struct Q *q = e->aq;
            switch (e->c) {
            case 1:
                if (q->gC < g_clock.t)
                    goto call;
                break;
            case 0:
            call:
                func_0028A920(p, j, q->g10 - q->gC);
                break;
            }
            func_0028AC30(p, j);
        }
    }
    func_00289F78(p, k);
}
