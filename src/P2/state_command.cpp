// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct CommandStateEntry;
struct CommandStateMethod {
    short delta, reserved;
    void (*function)(void *);
};
struct CommandStateDefinition {
    unsigned char prefix[0x18];
    int identifier;
};
struct CommandStateEntry {
    unsigned char prefix[0xC];
    CommandStateMethod *primary;
    int referenceCount;
    unsigned char reserved14[8];
    CommandStateEntry *next;
    CommandStateEntry *previous;
    CommandStateDefinition *definition;
    void *receiver;
};
struct StateCommandRecord {
    int primaryKey, secondaryKey, onIdentifier, offIdentifier;
};
extern "C" {
    extern CommandStateEntry *D_00479A08;
    void func_002BF218(void *, int);
    int func_0017DE98(void *, int, int, void *, int, void **);
    int func_0013B500(void *, int);
    void *func_001FBEC0(void *);
    void func_0013BD00(void *, int);
    void func_00239FE0(void *, int);
    void func_00239CE8(void *, int);
}
struct StateSearchScope {
    ~StateSearchScope() { func_002BF218(this, 2); }
};
extern "C" void *func_0023FB68(void *receiver, int identifier)
{
    StateSearchScope scope;
    CommandStateEntry *entry;
    for (entry=D_00479A08; entry; entry=entry->next) {
        if (entry->receiver==receiver) {
            if (identifier==-1||entry->definition->identifier==identifier)
                return entry;
        }
    }
    return 0;
}
extern "C" void func_0025D478(void *game, StateCommandRecord *command, void *owner,
                             int flags, int retentionKey, void **output)
{
    void *object;
    CommandStateEntry *entry;
    int identifier;
    if (output)
        *output=0;
    if (func_0017DE98(game, 0x204, command->primaryKey, owner, 1, &object)!=1)
        return;
    if (func_0013B500(object, 8)) {
        object=func_001FBEC0(object);
        if (!object)
            return;
    }
    if (!func_0013B500(object, 0x2F))
        return;
    entry=(CommandStateEntry *)func_0023FB68(object, command->secondaryKey);
    if (!entry)
        return;
    if (flags&1)
        identifier=command->onIdentifier;
    else
        identifier=command->offIdentifier;
    if (identifier==-1)
        return;
    if (retentionKey) {
        *output=entry;
        entry->primary[1].function((char *)entry+entry->primary[1].delta);
        func_0013BD00(entry, retentionKey);
    }
    if (flags&2)
        func_00239FE0(entry, identifier);
    else
        func_00239CE8(entry, identifier);
}
