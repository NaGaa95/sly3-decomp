// Remove original trailing12-byte object/message entries until the complete helper reduces count98 to zero. All four consumed receiver/object/message inputs are explicit; helper creates its own downstream callback and memory-move arguments.
// Reference compiler shape: src/hand/func_001DD820.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Entry {void *object;int first,second;};
struct S { char unknown_0[0x98]; int count; };
void func_0022B580(void *receiver,void *object,int first,int second);
void func_0022B828(struct S *p){while(p->count){struct Entry *entry=(struct Entry *)((char *)p+0x90)+p->count;func_0022B580(p,entry->object,entry->first,entry->second);}}
