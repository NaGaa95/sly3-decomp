// SLY3_CFLAGS: -Os -G0
struct Game { unsigned char prefix[0x3EB8]; int count; void *lists[1]; };
extern struct Game D_00475480;
extern char D_00479370[];
void func_001C85C0(void *object);
void func_00166228(void *list,void *object);
void func_0011B028(void *list,void *object);
void func_00273C28(void *object)
{
    int i;
    func_001C85C0(object);
    for(i=0;i<D_00475480.count;i++)
        func_00166228(D_00475480.lists[i],object);
    func_0011B028(D_00479370,object);
}
