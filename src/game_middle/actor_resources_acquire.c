// SLY3_CFLAGS: -Os -G0
struct Matrix4 { float elements[16]; } __attribute__((aligned(16)));
struct ResourceActor {
    unsigned char opaque0000[0x1190];
    void *resource1190;
    unsigned char opaque1194[0x1B10 - 0x1194];
    void *resource1B10;
};
extern struct Matrix4 D_003174C0;
void func_00152488(void *actor);
void func_00258958(void *record);
void *func_0023DDA0(void *owner, int identity, int kind);
void func_001C1410(void *actor, void *record, void **output);
void func_00271EE8(void *record);
void func_00155190(void *receiver, int id);
void *func_00130100(void *owner, void *channel, int mode, int identifier, struct Matrix4 *matrix);
void func_001DCCF0(void *actor, float gain);
void func_001DCD88(void *receiver)
{
    struct ResourceActor *actor = (struct ResourceActor *)receiver;
    char *base = (char *)receiver;
    void *channel;
    func_00152488(receiver);
    func_00258958(base + 0x1470);
    func_00258958(base + 0x15A0);
    func_00258958(base + 0x1680);
    actor->resource1190 = func_0023DDA0(receiver, 0x22, 1);
    func_001C1410(receiver, base + 0x1770, (void **)(base + 0x1870));
    func_00271EE8(base + 0x18E0);
    func_00155190(receiver, 0x2F);
    channel = func_0023DDA0(receiver, 0x23, 0xC);
    if (channel)
        actor->resource1B10 = func_00130100(receiver, channel, 1, 8, &D_003174C0);
    func_001DCCF0(receiver, 1.0f);
}
