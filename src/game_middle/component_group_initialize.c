// SLY3_CFLAGS: -Os -G0
struct PathSetupTemplate;
struct GroupOwner {
    void *actor;
    unsigned char opaque04[0x64];
    struct PathSetupTemplate *template68;
};
struct PathSetupTemplate *func_00150690(int type, void *owner, int key, int parent);
void func_00273E48(void *receiver, void *first, void *second, int mode);
void func_001B5890(void *group);
void func_001C1410(void *actor, void *record, void **output);
void func_00258958(void *record);
void func_00147E08(void *actor, int kind, int count, void *records, int a, int b, int c, void *result);
void func_002086B0(void *record, void *actor, void *optional);
void func_001B2720(void *receiver)
{
    struct GroupOwner *group = (struct GroupOwner *)receiver;
    char *base = (char *)receiver;
    group->template68 = func_00150690(0xE, 0, 0x169, -1);
    func_00273E48(group->template68, 0, 0, 0);
    func_001B5890(receiver);
    func_001C1410(group->actor, base + 0x70, (void **)(base + 0x170));
    func_001C1410(group->actor, base + 0x330, (void **)(base + 0x430));
    func_00258958(base + 0x180);
    func_00258958(base + 0x240);
    func_00147E08(group->actor, 0xC, 3, base + 0x2F0, 0, 0, 0, base + 0x314);
    func_002086B0(base + 0x440, group->actor, (char *)group->actor + 0x113C);
}
