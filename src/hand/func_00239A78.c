// Search the original eight-byte record array and return the matching index, or -1 when absent.
// Reference algorithm: src/hand/func_001DAE20.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { int id; int unknown; };
struct S { char prefix[0x40]; int count; struct E *entries; };
int func_00239A78(struct S *object,int id) { int i; for(i=0;i<object->count;i++) if(object->entries[i].id==id)return i;return -1; }
