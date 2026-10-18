// SLY3_CFLAGS: -Os -G0
struct RegistrationList {
    char prefix[0x45E8];
    int count;
    void *objects[16];
};
extern struct RegistrationList D_00475480;
int func_001F4630(void *object);
void func_001D2898(void *destination, void *source, unsigned int bytes);
void func_001F4670(void *object, int enable)
{
    int i;
    if (enable == func_001F4630(object))
        return;
    if (enable) {
        if ((unsigned int)D_00475480.count < 16)
            D_00475480.objects[D_00475480.count++] = object;
    } else {
        for (i = 0; i < D_00475480.count; i++) {
            if (D_00475480.objects[i] == object) {
                func_001D2898(&D_00475480.objects[i], &D_00475480.objects[i + 1], (D_00475480.count - i - 1) * 4);
                D_00475480.count--;
                break;
            }
        }
    }
}
