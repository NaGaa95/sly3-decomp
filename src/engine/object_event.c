// SLY3_CFLAGS: -Os -G0
struct ObjectEventOwner {
    char prefix[0x164];
    int state;
    unsigned int unused168;
    void *object;
};
void func_0013BEC0(void);
void func_0014DC98(void *receiver, int state);
void func_0014D8D0(struct ObjectEventOwner *owner, int message, void *source)
{
    func_0013BEC0();
    switch (message) {
    case 6:
        if (owner->state==5)
            func_0014DC98(owner, 0);
        break;
    case 9:
        if (source==owner->object) {
            switch (owner->state) {
            case 2: case 7:
                func_0014DC98(owner, 4);
                break;
            case 3:
                func_0014DC98(owner, 1);
                break;
            }
        }
        break;
    }
}
