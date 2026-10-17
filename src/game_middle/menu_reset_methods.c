// SLY3_CFLAGS: -Os -G0
struct Method { short adjustment, word2; void *function; };
struct MethodTable {
    unsigned char prefix[0x58];
    struct Method cancel;
    unsigned char gap[0x1B0 - 0x60];
    struct Method notify;
};
struct MenuChild {
    unsigned char prefix[0xC];
    struct MethodTable *methods;
};
struct MenuReset {
    unsigned char prefix[0xC];
    struct MethodTable *methods;
    unsigned char gap10[0x34 - 0x10];
    struct MenuChild *child;
    unsigned char gap38[0x50 - 0x38];
    int mode;
    float changedAt;
};
extern float D_0036BBD8;
extern int D_0046FC80;
int func_0021DD30(void *);
void func_001D0C88(struct MenuReset *menu)
{
    if (menu->mode != -1) {
        menu->mode = -1;
        menu->changedAt = D_0036BBD8;
    }
    if (func_0021DD30(menu)) {
        struct Method *method = &menu->methods->cancel;
        ((void (*)(void *))method->function)((char *)menu + method->adjustment);
    }
    if (menu->child) {
        struct Method *method = &menu->child->methods->notify;
        ((void (*)(void *))method->function)((char *)menu->child + method->adjustment);
    }
    D_0046FC80 = 0;
}
