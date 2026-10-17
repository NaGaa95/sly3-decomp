// SLY3_CFLAGS: -Os -G0
struct RegistrationList {
    char prefix[0x45E8];
    int count;
    void *objects[16];
};
extern struct RegistrationList D_00475480;
int func_001F4630(void *object)
{
    int i = D_00475480.count;
    while (--i >= 0)
        if (D_00475480.objects[i] == object)
            return 1;
    return 0;
}
