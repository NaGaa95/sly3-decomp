// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct EmitOwner;
struct Entry;
typedef struct SL SL;
struct OwnerFactoryMethod {
    short delta, reserved;
    union {
        void (*method)(void *);
        void (*set)(void *, int);
    } call;
};
struct OwnerFactoryObject {
    char opaque00[0xC];
    OwnerFactoryMethod *table;
    char opaque10[8];
    int state;
    char opaque1C[0x130 - 0x1C];
    int key;
    char opaque134[0x180 - 0x134];
};
struct OwnerFactoryGame {
    char opaque00[0x4818];
    char pool[0x48];
    EmitOwner *cached;
};
extern "C" {
void *func_0011E118(void *pool);
void *func_00292034(void *destination, int byte, unsigned int bytes);
void *func_002B69B0(void *storage);
Entry *func_0017DBD0(char *game, int key);
void func_0011AD80(SL *list, void *value);
}
typedef char OwnerFactorySize[(sizeof(OwnerFactoryObject) == 0x180) ? 1 : -1];
typedef char OwnerFactoryMethodSize[(sizeof(OwnerFactoryMethod) == 8) ? 1 : -1];

extern "C" EmitOwner *func_0020AFC0(void *context, int key)
{
    OwnerFactoryGame *game = static_cast<OwnerFactoryGame *>(context);
    EmitOwner *owner;
    if (key != 0 || (owner = game->cached) == 0) {
        void *storage = func_0011E118(game->pool);
        if (storage == 0) {
            owner = 0;
        } else {
            func_00292034(storage, 0, sizeof(OwnerFactoryObject));
            OwnerFactoryObject *created = static_cast<OwnerFactoryObject *>(func_002B69B0(storage));
            created->key = key;
            func_0011AD80(reinterpret_cast<SL *>(func_0017DBD0(static_cast<char *>(context), 0x63)), created);
            created->state = 10;
            OwnerFactoryMethod *method = &created->table[7];
            method->call.method(reinterpret_cast<char *>(created) + method->delta);
            method = &created->table[11];
            method->call.method(reinterpret_cast<char *>(created) + method->delta);
            method = &created->table[17];
            method->call.method(reinterpret_cast<char *>(created) + method->delta);
            method = &created->table[29];
            method->call.set(reinterpret_cast<char *>(created) + method->delta, 0);
            if (key == 0)
                game->cached = reinterpret_cast<EmitOwner *>(created);
            owner = reinterpret_cast<EmitOwner *>(created);
        }
    }
    return owner;
}
