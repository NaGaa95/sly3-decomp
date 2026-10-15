// Count the four original60-byte entries whose first active word is nonzero. The receiver is the only consumed input and the result is the actual count, with no callback or inferred unused formal.
// Reference compiler shape: src/hand/func_00153FF8.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Entry {int active;char remainder[0x5C];};
struct S {char prefix[0x194];struct Entry entries[4];};
int func_00205A38(struct S *p){unsigned int i;int count=0;for(i=0;i<4;i++)if(p->entries[i].active)count++;return count;}
