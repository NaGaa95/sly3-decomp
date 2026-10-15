// Return the indexed28-byte embedded record only when the original index-plus-one bound permits it; retain the original sentinel behavior without adding a negative-index check.
// Reference algorithm: src/hand/func_001A66C8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record { char bytes[0x1C]; };
struct S { char prefix[0x3C0];int count;char unknown[0x3E0-0x3C4];struct Record records[0]; };
struct Record *func_0020ADF0(struct S *p,int index){if(index+1<p->count)return p->records+index;return 0;}
