// Apply the original two-pointer resource update to each unflagged D0-byte record. Both helper receivers and entries are explicit; the original mask is a field condition and is not an unconsumed third callee argument.
// Reference algorithm: src/hand/func_00201E88.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Entry {char prefix[0x18];unsigned long flags;char remainder[0xD0-0x20];};
struct S { char unknown_0[0xD0]; int count; struct Entry * entries; };
void func_0023B720(void *receiver,void *entry);
void func_0023B9C8(struct S *p){int i;struct Entry *entry;for(i=0;i<p->count;i++)if(!((entry=p->entries+i)->flags&0x80000))func_0023B720(p,entry);}
