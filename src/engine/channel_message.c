// SLY3_CFLAGS: -Os -G0
struct ChannelMessageOwner {
    char prefix[0x4C];
    void *channel;
    char unused50[0x1B8-0x50];
    unsigned int enabledWord;
};
struct ChannelMessageState {
    char prefix[0x10];
    struct ChannelMessageOwner *owner;
    char unused14[0x24];
    int blocked;
    unsigned int unused3C;
    void *clip;
    unsigned int restoreWord;
};
struct ChannelMessage {
    int key, unused4, command;
};
int func_00254F80(void *clip);
int func_00131850(void *receiver, int message, void *arguments);
void func_0028F068(void *owner, void *channel, int mode);
int func_00131C98(struct ChannelMessageState *state, int message, struct ChannelMessage *arguments)
{
    if (message==10 && state->clip && func_00254F80(state->clip)==arguments->key) {
        switch (arguments->command) {
        case 0x44:
            state->owner->enabledWord=1;
            func_0028F068(state->owner, state->owner->channel, 2);
            return 1;
        case 0x45:
            state->owner->enabledWord=state->restoreWord;
            if (!state->blocked)
                func_0028F068(state->owner, state->owner->channel, 1);
            return 1;
        }
    }
    return func_00131850(state, message, arguments);
}
