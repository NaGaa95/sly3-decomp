// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S;
struct ActorScalarDefaultsView {
    char prefix[0x154];
    float scalar154;
    char reserved158[0x18C - 0x158];
    float scalar18C;
    char reserved190[0x1A0 - 0x190];
    float scalar1A0, scalar1A4;
};
void func_001F65F0(struct S *receiver);

void func_001F9130(struct S *receiver) {
    struct ActorScalarDefaultsView *p = (struct ActorScalarDefaultsView *)receiver;
    func_001F65F0(receiver);
    p->scalar18C = 450.0f;
    p->scalar154 = 0.75f;
    p->scalar1A0 = 50.0f;
    p->scalar1A4 = 150.0f;
}

typedef char ActorScalarDefaultsWidths[(sizeof(void *) == 4 && sizeof(float) == 4 && sizeof(struct ActorScalarDefaultsView) == 0x1A8) ? 1 : -1];
