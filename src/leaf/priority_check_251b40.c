// SLY3_CFLAGS: -Os -G0
struct Actor {
    unsigned char prefix[0x130];
    int kind;
    unsigned char gap134[0x188 - 0x134];
    void *target;
};
struct Candidate {
    unsigned char prefix[0x14];
    struct Actor *actor;
    unsigned char gap18[0x50 - 0x18];
    unsigned int flags;
};
int func_0013B500(void *actor, int key);
int func_002533C0(void *owner, int state);
int func_00250290(void *owner, struct Candidate *item);
int func_00251B40(void *owner, struct Candidate *item)
{
    if (func_0013B500(item->actor, 0x71) && item->actor->kind == 6 && item->actor->target == owner)
        return 1;
    if (func_002533C0(owner, 5) || func_002533C0(owner, 6) || func_002533C0(owner, 0x23)) {
        if (func_0013B500(item->actor, 0x72) && (item->flags & 0x2C))
            return 1;
    }
    return func_00250290(owner, item);
}
