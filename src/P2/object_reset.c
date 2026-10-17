// SLY3_CFLAGS: -Os -G0
struct Entry {
    short delta,unused;
    union {
        void (*one)(void *,int);
        void (*five)(void *,int,int,int,int,int);
    };
};
struct Object {
    unsigned char prefix[0xC];
    struct Entry *vtable;
    unsigned char gap10[0x5C];
    int index;
    unsigned char gap6C[4];
    void *record;
    int counter;
    unsigned char gap7C[0x20];
    int active;
};
void func_00267860(void *record);
void func_00263080(struct Object *object,int mode);
void func_002621F0(struct Object *object)
{
    struct Entry *entry;
    func_00267860(object->record);
    if(object->active)
        func_00263080(object,-1);
    entry=&object->vtable[23];
    entry->one((char *)object+entry->delta,0);
    entry=&object->vtable[3];
    entry->five((char *)object+entry->delta,6,0,0,0,0);
    object->counter=0;
    object->index=-1;
}
