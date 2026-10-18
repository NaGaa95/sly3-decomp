// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void *); };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct Entry { unsigned flags; struct Object *object; };
struct Game { unsigned char prefix[0x4648]; int entryCount; unsigned char gap464C[8]; struct Entry *entries; };
extern struct Game D_00475480;
void func_002429C8(void)
{
    int count=D_00475480.entryCount;
    if(count) {
        struct Entry *entries=D_00475480.entries;
        unsigned flags=entries[0].flags;
        int i;
        for(i=0;i<count;i++) {
            unsigned next=entries[i+1].flags;
            if((flags&0x44)==4) {
                struct Method *method=&entries[i].object->methods[19];
                method->method((char *)entries[i].object+method->delta);
            }
            flags=next;
        }
    }
}
