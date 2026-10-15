// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Resolve ordinary and alias buckets using the original count/capacity protocol.
typedef struct LO LO;
typedef struct CH CH;
struct LO {
    char unused00[0x10];
    LO *parent;
    int unused14;
    int key;
    LO *next_key;
    char unused20[8];
    union {
        unsigned long flags;
        struct {
            unsigned long reserved40 : 40;
            unsigned int priority : 4;
            unsigned int reserved44 : 12;
            unsigned int enabled : 1;
        } bits;
    } packed;
    char unused30[8];
    CH *scope;
};
struct Alias {
    int handle;
    CH *scope;
    int key;
    struct Alias *next;
    LO *object;
};
struct ObjectBucket { LO *head; };
struct AliasBucket { struct Alias *head; };
typedef char CheckInt[(sizeof(int) == 4) ? 1 : -1];
typedef char CheckPointer[(sizeof(LO *) == 4) ? 1 : -1];
typedef char CheckFlags[(sizeof(unsigned long) == 8) ? 1 : -1];
class ObjectToken { public: ~ObjectToken(); };
class AliasToken { public: ~AliasToken(); };
typedef char CheckTokenSizes[(sizeof(ObjectToken) == 1 && sizeof(AliasToken) == 1) ? 1 : -1];
extern "C" {
extern struct ObjectBucket *func_0017DBA8(void *, int);
extern struct AliasBucket *func_0017DBE8(void *, int);
extern void func_0017DC10(void *, LO *, CH *, unsigned int,
                        void *, CH *, int, int *, LO **, int *);

extern CH *D_00479AB4;
}

extern "C" int func_0017DEC0(void *game, int flags, int key, LO *owner,
                  CH *scope, int capacity, LO **output)
{
    int count;
    int best_depth;
    LO *marked;
    LO *object;
    struct Alias *alias;

    if (key == -1 || (!owner && (flags & 0xFF) != 5))
        return 0;
    if (!scope)
        scope = owner ? owner->scope : D_00479AB4;
    count = 0;
    switch (flags & 0xFF) {
    case 1:
    case 3:
    case 4: {
        unsigned int depth = 0;
        marked = owner;
        for (object = marked; object; object = object->parent) {
            object->packed.bits.priority = ++depth;
        }
        best_depth = 0x7FFFFFFF;
        break;
    }
    default:
        marked = 0;
        break;
    }

    ObjectToken object_token;
    func_0017DBA8(game, key);
    for (object = func_0017DBA8(game, key)->head;
         object; object = object->next_key) {
        if (object->key == key)
            func_0017DC10(game, object, object->scope, flags, owner, scope,
                          capacity, &count, output, &best_depth);
    }
    AliasToken alias_token;
    func_0017DBE8(game, key);
    for (alias = func_0017DBE8(game, key)->head; alias; alias = alias->next) {
        if (alias->key == key && alias->object) {
            if (alias->object->key == key) {
                int i;
                for (i = 0; i < count; ++i)
                    if (output[i] == alias->object)
                        break;
                if (i < count)
                    continue;
            }
            func_0017DC10(game, alias->object, alias->scope, flags, owner, scope,
                          capacity, &count, output, &best_depth);
        }
    }
    for (object = marked; object; object = object->parent)
        object->packed.flags &= ~(15UL << 40);
    if (!(flags & 0x200) && capacity < count)
        count = capacity;
    return count;
}
