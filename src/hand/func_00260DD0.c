// Copy up to ten explicit command values into the original embedded array and invoke its adjusted completion method.
// Reference algorithm: src/hand/func_00212880.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct PMF { short adjustment;short reserved;void (*method)(void *); };
struct S {char prefix[0xC];struct PMF *vtable;char reserved[0xBC-0x10];int values[10]; };
void func_00260DD0(struct S *p,int count,const int *values){int i;struct PMF *slot;for(i=0;i<count && (unsigned int)i<10;i++)p->values[i]=*values++;slot=p->vtable+56;slot->method((char *)p+slot->adjustment);}
