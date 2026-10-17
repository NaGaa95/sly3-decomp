// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Item { unsigned char prefix[0x3C]; struct Item *next; };
struct Owner {
    unsigned char prefix[0x4C]; struct Item *first; unsigned char gap50[0xC];
    int word5C; int word60; unsigned char gap64[4]; int word68; unsigned char gap6C[8];
    void *attachment; unsigned char gap78[0xC4]; int word13C; unsigned char gap140[0xD4];
    int count; struct Item *items[8]; struct Item *selected;
};
extern qword D_00317560;
extern unsigned char D_004BC220[];
void func_00248DF8(void *owner);
void func_00248740(void *owner);
void func_0027ED18(void *record);
void func_00173E48(void *space,qword position,int word,void **output);
void func_00244CA8(void *item,float value);
void func_00247588(struct Owner *owner)
{
    struct Item *item;
    struct Item *last;
    func_00248DF8(owner);
    func_00248740(owner);
    func_0027ED18(D_004BC220);
    func_00173E48(0,D_00317560,0,&owner->attachment);
    for(item=owner->first;item;item=item->next) {
        if(item==owner->selected)
            continue;
        if(owner->count>0)
            last=((struct Item **)&owner->count)[owner->count];
        else
            last=0;
        if(item==last)
            continue;
        func_00244CA8(item,0.0f);
    }
    owner->word5C=0;
    owner->word60=0;
    owner->word13C=0;
    owner->word68=3;
}
