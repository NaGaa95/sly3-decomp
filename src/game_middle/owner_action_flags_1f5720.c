// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern void *D_0036B250;
extern unsigned int D_00346F80[];
int func_00140738(void *transported_unused);
unsigned int func_00154798(void *receiver, int kind);
int func_001F5720(void *unused_receiver, int selector)
{
    switch (selector) {
    case 12: return 0x204;
    case 0: return 0x25A;
    case 2: return 0x25B;
    case 4: return 0x25C;
    case 1: return 0x25D;
    case 10: return 0x203;
    case 8:
        if (func_00140738(D_0036B250))
            return 0x25E;
        break;
    case 5:
    case 6:
    case 9:
        if (func_00154798(D_0036B250, 13) & D_00346F80[selector])
            return 0x25F;
        break;
    }
    return -1;
}
