// SLY3_CFLAGS: -Os -G0
struct ObjectView {
    unsigned char opaque00[0x34];
    float f34;
    unsigned char opaque38[4];
    int i3C;
    unsigned char opaque40[4];
    float f44;
    float f48;
    float f4C;
    unsigned char opaque50[0x30];
    int i80;
};
void func_00238970(void *);
void func_001D8008(void *receiver)
{
    struct ObjectView *object = (struct ObjectView *)receiver;
    func_00238970(receiver);
    object->f34 = -1.0f;
    object->f44 = 100.0f;
    object->f48 = 25.0f;
    object->f4C = 60.0f;
    object->i3C = -1;
    object->i80 = 1;
}
