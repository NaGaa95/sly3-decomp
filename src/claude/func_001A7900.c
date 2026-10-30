// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Player { unsigned char storage[0x11C0]; };
extern struct Player D_0036E740[];
int func_001A7AE0(struct Player *player, void *a, void *b);
int func_001A7900(void *a, void *b)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (func_001A7AE0(&D_0036E740[i], a, b)) {
            return i;
        }
    }
    return -1;
}
