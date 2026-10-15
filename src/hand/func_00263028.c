// Search the actual20-byte entry collection for the incoming integer ID, returning false for the original -1 sentinel. Historical context A0 is unused by the complete body and remains provisional; collection A1/ID A2 are actual consumed inputs.
// Reference algorithm: src/hand/func_002142B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Entry {char prefix[0x10];int identifier;};
struct Collection {unsigned short count;unsigned short unused;struct Entry *entries;};
int func_00263028(void *context,struct Collection *collection,int identifier){int i;struct Entry *entry;if(identifier==-1)return 0;for(i=0;i<collection->count;i++)if(identifier==(entry=collection->entries+i)->identifier)return 1;return 0;}
