// SLY3_CFLAGS: -Os -G0
struct Vector3 { int x,y,z; };
struct Entry { short delta,unused; void (*method)(void *); };
struct Target { unsigned char prefix[0xC]; struct Entry *vtable; };
struct Object {
    unsigned char prefix[0x30];
    struct Target *target;
    int word34,word38,word3C,word40;
    unsigned char gap44[0xC];
    struct Vector3 first;
    int pad5C;
    struct Vector3 second;
};
void func_00222CD8(struct Object *object)
{
    struct Vector3 *first=&object->first;
    struct Vector3 *second=&object->second;
    struct Target *target;
    struct Entry *entry;
    object->word3C=0;
    object->word40=0;
    first->z=0;
    first->y=0;
    object->first.x=0;
    second->z=0;
    second->y=0;
    object->second.x=0;
    object->word34=0;
    object->word38=0;
    target=object->target;
    if(target) {
        entry=&target->vtable[54];
        entry->method((char *)target+entry->delta);
    }
}
