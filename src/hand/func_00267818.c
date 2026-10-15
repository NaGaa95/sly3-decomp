// Read the signed selection from the actual24-byte indexed entry and reset its20-byte record when valid. Complete269F88 also consumes the original incoming index A1; that second argument is explicitly forwarded.
// Reference algorithm: src/hand/func_0017F6B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Entry {int count;void *items;short selection;char unknown[14];};
struct Record {char bytes[20];};
struct S {int unknown;struct Record *records;struct Entry *entries;};
void func_00269F88(void *record,int index);
void func_00267818(struct S *p,int index){int selection=p->entries[index].selection;if(selection>=0)func_00269F88(&p->records[selection],index);}
