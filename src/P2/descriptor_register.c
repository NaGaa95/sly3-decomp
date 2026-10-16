// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
struct RegistrationProperty {
    char prefix[0xD8];
    int mode;
    char gapDC[0x18];
    DL *secondary;
};
void func_001C85E8(void *receiver);
void func_0011AF60(DL *list, void *node);
void *func_001FE728(void *receiver, int flags);

void func_001FE6B0(void *receiver)
{
    struct RegistrationProperty *property = receiver;
    func_001C85E8(receiver);
    switch (property->mode) {
    case 2:
        func_0011AF60(property->secondary, receiver);
    case 1:
    case 3:
        func_001FE728(receiver, 1);
        break;
    }
}
