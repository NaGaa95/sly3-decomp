// Look up the value stored for id (cached on the current world when it matches, otherwise read through its key) and report it.
// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
struct Key { int word; };
struct Entry {
    unsigned char opaque00[0x44];
    int cached;
    unsigned char opaque48[0xE8 - 0x48];
    struct Key key;
};
struct World {
    unsigned char opaque00[0xF8];
    unsigned int id;
    struct Entry *entry;
};
struct Game {
    unsigned char opaque00[0x4044];
    struct World *current;
    unsigned char opaque4048[0x4088 - 0x4048];
    struct Key *keys[0x43];
};
extern struct Game D_00475480;
extern unsigned char D_00468D30[];
extern int D_0036DB98;
struct World *func_0017E1B8(struct Game *game, int kind, int id, void *other);
CRef *func_002BC010(CRef *output, struct Key *key, unsigned char *buffer);


int func_0021F410(unsigned int id)
{
    CRef value;
    int result;
    struct World *world;
    if (id >= 0x43) return 0;
    world = D_00475480.current;
    {
        int missing = (world == 0 && D_0036DB98 != -1);
        if (missing) world = func_0017E1B8(&D_00475480, 0x105, D_0036DB98, 0);
    }
    if (world && world->id == id) {
        struct Entry *entry = world->entry;
        result = entry->cached;
        if (result == -1) {
            struct Key *key = &entry->key;
            if (key->word) {
                func_002BC010(&value, key, D_00468D30);
                result = value.payload.integer;
                func_0012BC20(&value);
            }
        }
        return result >= 2;
    }
    func_002BC010(&value, D_00475480.keys[id], D_00468D30);
    result = value.payload.integer;
    func_0012BC20(&value);
    return result;
}
