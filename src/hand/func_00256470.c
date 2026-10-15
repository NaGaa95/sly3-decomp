// Find the explicit array value, decrease its count and move the following pointer entries into its position with actual byte count. Both search and copy arguments remain explicit.
// Reference algorithm: src/hand/func_0017DDE8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S {char prefix[0x28];int count;void *entries[0];};
int func_002562D8(struct S *p,void *value);
void func_001D2898(void *destination,const void *source,int bytes);
void func_00256470(struct S *p,void *value){int index=func_002562D8(p,value);if(index>=0){void **entry=p->entries+index;--p->count;func_001D2898(entry,entry+1,4*(p->count-index));}}
