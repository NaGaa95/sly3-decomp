// Menu confirm/cancel button handling once the highlighted item has settled: mode 1 records the choice (-1 / 0), mode 2/3 starts the transition, otherwise a single button confirms; all paths notify through vtable slot 11.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VEntry { short delta, pad; void (*call)(void *); };
struct Item { unsigned char pad0[0x48]; int state; float pressedAt; unsigned char pad50[4]; int target; };
struct Menu {
    unsigned char pad00[0xC];
    VEntry *table;
    unsigned char pad10[0x1C - 0x10];
    void *controller;
    unsigned char pad20[0x30 - 0x20];
    int mode;
    Item *item;
};
extern unsigned char D_00475480[];
extern unsigned char D_00468D30[];
extern int D_0036DBA4;
extern float D_0036BBD8;
extern "C" {
int func_0025AE28(void *game);
int func_001A7A80(void *controller, int button, float hold);
void func_00289198(void *game, int a, int b, void *context);
}
extern "C" void func_00222E48(Menu *self)
{
    Item *item = self->item;
    if (!item) return;
    if (item->state != 2) return;
    if (item->target != item->state) return;
    if (func_0025AE28(D_00475480)) return;
    if (D_0036BBD8 - self->item->pressedAt <= 0.1f) return;
    switch (self->mode) {
    case 1:
        if (!self->controller) return;
        if (func_001A7A80(self->controller, 0x80, 0.0f)) {
            register int value __asm__("$2") = -1; /* register pin: -1 goes through v0 ahead of the address like the target */
            D_0036DBA4 = value;
        } else if (func_001A7A80(self->controller, 0x10, 0.0f))
            D_0036DBA4 = 0;
        else
            return;
        self->table[11].call((char *)self + self->table[11].delta);
        break;
    case 2:
    case 3:
        if (!self->controller) return;
        if (func_001A7A80(self->controller, 0x80, 0.0f))
            func_00289198(D_00475480, 2, 0, D_00468D30);
        else if (!func_001A7A80(self->controller, 0x10, 0.0f))
            return;
        self->table[11].call((char *)self + self->table[11].delta);
        break;
    default:
        if (!self->controller) return;
        if (func_001A7A80(self->controller, 0x40, 0.0f))
            self->table[11].call((char *)self + self->table[11].delta);
        break;
    }
}
