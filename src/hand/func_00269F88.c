// Visit the selected original resource group in reverse, forwarding each actual entry to object cleanup or the original intrusive free list.
// SLY3_CFLAGS: -Os -G0
struct Entry {char prefix[0x30];void *object;int kind;char unknown[0x20];int index;char remainder[0x14];};
struct Group {int count;struct Entry *entries;char unknown[0x10];};
struct Header {char prefix[8];struct Group *groups;char unknown[0x18];void *manager;};
struct S {char prefix[0xC];struct Header *header;};
void func_002647A0(void *object,struct Entry *entry);
void func_0011ADA8(void *list,struct Entry *entry);
void func_00269F88(struct S *p,int index){struct Group *group=(struct Group *)(index*sizeof(struct Group)+(unsigned int)p->header->groups);int i=group->count-1;struct Entry *entries=group->entries;for(;i>=0;i--){struct Entry *entry=&entries[i];if(entry->object)func_002647A0(entry->object,entry);else if(entry->kind==4)func_0011ADA8((char *)p->header->manager+0xF4,entry);}}
