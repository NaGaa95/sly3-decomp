// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct Actor {
    char prefix[0xFA0];
    struct Actor *related;
};

struct Game;
extern struct Game D_00475480;
struct Actor *func_001F4AD0(struct Game *unused, int player);
int func_0013B500(struct Actor *actor, int kind);
struct Actor *func_0017E1B8(struct Game *game, int flags, int identifier,
                          struct Actor *context);

static __inline__ struct Actor *Related(struct Actor *actor)
{
    return actor && func_0013B500(actor, 0x33) ? actor->related : actor;
}

struct Actor *func_001E8A38(int identifier)
{
    struct Actor *result;
    switch (identifier) {
    case 0x304: {
        struct Actor *actor = Related(func_001F4AD0(&D_00475480, 0));
        result = func_0017E1B8(&D_00475480, 1, identifier, actor);
        break;
    }
    case 0x305:
        result = func_0017E1B8(&D_00475480, 1, 0x305,
                            func_001F4AD0(&D_00475480, 0));
        break;
    default:
        result = func_0017E1B8(&D_00475480, 0x405, identifier, 0);
        break;
    }
    return result;
}
