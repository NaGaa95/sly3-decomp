// SLY3_CFLAGS: -Os -G0
struct Record { unsigned char prefix[0x94]; int key; int pad98; int variant; unsigned char gapA0[0x60]; };
struct Group { unsigned char prefix[0x40]; int count; struct Record *records; };
struct Handle { unsigned char prefix[0x20]; struct Group *group; struct Record *record; unsigned char gap28[8]; };
void *func_001C9A50(unsigned bytes);
void *func_002BF2F0(void *object);
struct Handle *func_00241E10(struct Group *group,int variant,int key)
{
    int i;
    for(i=0;i<group->count;i++) {
        struct Record *record=&group->records[i];
        if(record->key==key&&(variant==-1||record->variant==variant)) {
            struct Handle *handle=func_002BF2F0(func_001C9A50(0x30));
            handle->group=group;
            handle->record=record;
            return handle;
        }
    }
    return 0;
}
