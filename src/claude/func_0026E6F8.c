// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of the Sly 2 source src/hand/func_0021C0D8.c (offsets updated).
struct VT { short d0; short p0; void *f0; char pad[0x40]; short d9; short p9; void (*pf9)(void *); };
struct S { char pad[0xC]; struct VT *pvt; char pad10[0x104 - 0x10]; float x12C; float x130; char pad134[0x13C - 0x10C]; int x158; char pad15c[0x148 - 0x140]; int x164; };
extern struct CLOCK { float t; float dt; } g_clock;
void func_001C8168(struct S *p);
void func_0026E6F8(struct S *p)
{
    func_001C8168(p);
    if (p->x130 != 0.0f) {
        float t = p->x12C + g_clock.dt * p->x130;
        p->x12C = t;
        if (t <= 0.0f) {
            p->x12C = 0.0f;
            p->x130 = 0.0f;
        } else if (1.0f <= t) {
            p->x12C = 1.0f;
            p->x130 = 0.0f;
        }
    }
    if (p->x12C <= 0.0f && p->x130 <= 0.0f && !(p->x164 < p->x158))
        ((void (*)(void *))p->pvt->pf9)((char *)p + p->pvt->d9);
}
