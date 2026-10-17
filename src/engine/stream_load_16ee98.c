// SLY3_CFLAGS: -Os -G0
struct LoadRequest { int bytes; int alignment; };
struct LoadItem { unsigned char payload[0x40]; int first; int second; };
struct LoadLink { int kind; int first; int second; };
struct LoadOwner {
    unsigned char prefix[0x40]; int itemCount; struct LoadItem *items; int linkCount; struct LoadLink *links;
    unsigned char heap[0x10]; int heapSize; unsigned char block[0x694 - 0x64]; int blocks;
};
extern unsigned char *D_00479DB0;
void func_001C7D98(void *owner, void *stream);
int func_001191E0(void *stream);
int func_00119128(void *stream);
void func_00119948(void *stream, void *destination);
void *func_001D2538(struct LoadRequest *request);
void *func_001D2470(struct LoadRequest *request);
void func_00117E78(void *heap, int size, void *base);
int func_00196C18(void *table, int count);
void func_00196AA8(void *block, int first, int last);
void func_0016EE98(struct LoadOwner *owner, void *stream)
{
    struct LoadRequest request;
    int i, j, size, first, pages;
    func_001C7D98(owner, stream);
    owner->itemCount = func_001191E0(stream);
    request.bytes = owner->itemCount * 0x48;
    request.alignment = 0x10;
    owner->items = (struct LoadItem *)func_001D2538(&request);
    for(i = 0; i < owner->itemCount; i++) {
        struct LoadItem *item = owner->items + i;
        func_00119948(stream, item);
        item->first = func_001191E0(stream);
        item->second = func_001191E0(stream);
    }
    owner->linkCount = func_001191E0(stream);
    request.bytes = owner->linkCount * 0xC;
    request.alignment = 0x10;
    owner->links = (struct LoadLink *)func_001D2538(&request);
    for(j = 0; j < owner->linkCount; j++) {
        struct LoadLink *link = owner->links + j;
        link->kind = func_00119128(stream);
        switch(link->kind) {
        case 1:
            link->first = func_001191E0(stream);
            link->second = func_001191E0(stream);
            break;
        case 0:
        case 2:
            link->first = func_001191E0(stream);
            break;
        }
    }
    size = owner->heapSize;
    if(!size) size = 0x20000;
    request.bytes = size;
    request.alignment = 0x10;
    func_00117E78(owner->heap, size, func_001D2470(&request));
    pages = (owner->blocks + 0xFF) / 256;
    first = func_00196C18(D_00479DB0, pages);
    func_00196AA8(owner->block, first, first + pages);
}
