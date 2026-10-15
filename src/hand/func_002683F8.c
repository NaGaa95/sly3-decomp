// Inspect the explicit sixteen-byte entry and update the stored context for selected entries; outer index A1 and selection A2 remain explicit, and helper consumes context/selection.
// Reference algorithm: src/hand/func_001B0808.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Entry {int unused;unsigned int flags;int unknown[2];};
struct S {int unused;struct Entry *entries;int unknown;void *context;};
void func_00267970(void *context,int selection);
void func_002683F8(struct S *p,int index,int selection){struct Entry *entry=p->entries+index;if(entry->flags&0x01000000)func_00267970(p->context,selection);}
