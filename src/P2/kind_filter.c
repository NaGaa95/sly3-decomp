// SLY3_CFLAGS: -Os -G0
struct Item { unsigned char prefix[0x20]; int kind; unsigned char gap24[4]; int pending; };
int func_00250290(void *owner,struct Item *item)
{
    if(!item->pending)
        return 0;
    switch(item->kind) {
    case 0:
    case 1:
    case 0x80000:
    case 0x100000:
        return 0;
    }
    return 1;
}
