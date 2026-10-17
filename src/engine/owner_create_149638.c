// SLY3_CFLAGS: -Os -G0
struct CreateEntry { short delta; short pad; union { void (*method)(void *); void (*set)(void *, int); } call; };
struct CreateObject { unsigned char prefix[0xC]; struct CreateEntry *table; unsigned char gap10[8]; int state; };
void *func_0011E118(void *pool);
void *func_00292034(void *destination, int byte, unsigned int bytes);
struct CreateObject *func_002B69E8(void *storage);
void *func_0017DBD0(char *game, int key);
void func_0011AD80(void *list, void *value);
struct CreateObject *func_00149638(char *self)
{
    void *storage;
    struct CreateObject *object;
    if(!*(int *)(self + 0x4870)) {
        if(*(int *)(self + 0x4878)) return 0;
    }
    storage = func_0011E118(self + 0x4864);
    func_00292034(storage, 0, 0x450);
    object = func_002B69E8(storage);
    func_0011AD80(func_0017DBD0(self, 0x1A), object);
    object->state = 9;
    object->table[7].call.method((char *)object + object->table[7].delta);
    object->table[11].call.method((char *)object + object->table[11].delta);
    object->table[17].call.method((char *)object + object->table[17].delta);
    object->table[29].call.set((char *)object + object->table[29].delta, 0);
    return object;
}
