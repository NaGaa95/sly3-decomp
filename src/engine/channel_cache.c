// SLY3_CFLAGS: -Os -G0
struct ChannelCacheState {
    char prefix[0x10];
    void *owner;
    char unused14[0x3C-0x14];
    int selection;
    void *entry;
};
void func_00238978(void);
void func_00252E40(void *owner, int selection);
void *func_002553D8(void *owner);
void func_00131610(void *receiver, int mode);
void func_00255038(void *entry, void *owner);
void func_00131598(void *receiver)
{
    struct ChannelCacheState *state=receiver;
    func_00238978();
    func_00252E40(state->owner, state->selection);
    if (!state->entry) {
        state->entry=func_002553D8(state->owner);
        if (!state->entry) {
            func_00131610(state, 1);
            return;
        }
    }
    func_00131610(state, 0);
    func_00255038(state->entry, state->owner);
}
