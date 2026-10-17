// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Item { unsigned char prefix[0x20]; float scaleX; float scaleY; unsigned char gap28[0x2C]; };
struct Record { unsigned char prefix[0x10]; int word10; unsigned char gap14[0xC]; qword colour; };
struct Manager { unsigned char prefix[0x690]; unsigned count; unsigned current; struct Item items[8]; };
extern qword D_00317530;
struct Record *func_0028A480(struct Manager *manager,int a,int b);
void func_0028AF48(struct Manager *manager)
{
    if(manager->count<8) {
        struct Item *item=&manager->items[manager->count];
        struct Record *record;
        item->scaleX=1.0f;
        item->scaleY=1.0f;
        manager->current=manager->count;
        manager->count++;
        record=func_0028A480(manager,0,2);
        record->word10=0;
        record->colour=D_00317530;
    }
}
