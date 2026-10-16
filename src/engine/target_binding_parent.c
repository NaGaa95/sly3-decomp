// SLY3_CFLAGS: -Os -G0
struct ACTOR_FIELD { int flags, identifier, offset; };
extern const struct ACTOR_FIELD D_00342CC0[];
void func_00137628(void *effect);
void func_001C8970(void *actor, int count, const struct ACTOR_FIELD *fields, void *parent);
struct TargetFields {
    char unaccessed0[0x214];
    void *target;
    char unaccessed218[0x228-0x218];
    unsigned char effect228[12], effect234[12];
};
void func_00146FD0(struct TargetFields *p, void *target)
{
    if (target != p->target) {
        func_00137628(p->effect228);
        func_00137628(p->effect234);
        p->target = target;
        if (target)
            func_001C8970(p, 7, D_00342CC0, target);
    }
}
