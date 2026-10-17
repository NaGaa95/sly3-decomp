// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void *,int,int,int); };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct Record { struct Object *object; unsigned char gap4[0x14]; };
struct Group { unsigned char prefix[0x48]; int count; struct Record *records; };
void func_002395E8(struct Group *group,int unused,int a,int b)
{
    int i;
    for(i=0;i<group->count;i++) {
        int offset=i*sizeof(struct Record);
        struct Object *object=((struct Record *)((char *)group->records+offset))->object;
        if(object) {
            struct Method *entry=&object->methods[15];
            entry->method((char *)object+entry->delta,-1,a,b);
        }
    }
}
