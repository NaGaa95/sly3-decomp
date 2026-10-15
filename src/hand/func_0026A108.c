// Find the first matching explicit identifier in the original embedded array of twelve-byte records.
// Reference algorithm: src/hand/func_001F5FF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { int id;int first;int second; };
struct S { char prefix[0x120];int count;struct E entries[0]; };
struct E *func_0026A108(struct S *p,int id){int i;struct E *entry;for(i=0;i<p->count;i++)if((entry=p->entries+i)->id==id)return entry;return 0;}
