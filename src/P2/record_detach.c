// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct Link { unsigned char prefix[8]; struct Object *back; };
struct Record { struct Object *object; int unknown_4; struct Link *link; };
struct Owner { unsigned char prefix[0x48]; int count; };
static inline void CallObject(struct Object *object,int slot)
{
    ((void (*)(void *))object->methods[slot].method)((char *)object+object->methods[slot].delta);
}
void func_0021AB48(struct Owner *owner,struct Record *record)
{
    struct Link *link;
    CallObject(record->object,9);
    link=record->link;
    record->object=0;
    link->back=0;
    record->link=0;
    owner->count--;
}
