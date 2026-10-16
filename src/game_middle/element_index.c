// SLY3_CFLAGS: -Os -G0
struct IndexedElement { unsigned char bytes[32]; };
struct ElementPool { int unused0; struct IndexedElement *base; };

int func_001EBD40(void *receiver, struct IndexedElement *element)
{
    return element - ((struct ElementPool *)receiver)->base;
}
