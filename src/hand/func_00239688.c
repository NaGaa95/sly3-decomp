// Traverse every original24-byte entry and notify each non-null object with the explicit absent selector. Indirect receiver/selector API remains provisional; original caller setup is retained.
// Reference algorithm: src/hand/func_001F2B20.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V { short delta;short unused;void (*method)(void *,int); };
struct Object { char prefix[0xC];struct V *vtable; };
struct Entry { struct Object *object;int unknown[5]; };
struct S { char prefix[0x48];int count;struct Entry *entries; };
void func_00239688(struct S *p){int i;struct Entry *entry;for(i=0;i<p->count;i++){struct Object *object=(entry=p->entries+i)->object;if(object)object->vtable[16].method((char *)object+object->vtable[16].delta,-1);}}
