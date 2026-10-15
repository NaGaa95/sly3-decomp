// Copy the complete original sixteen-byte mask with its natural four-byte alignment and return the result of the receiver/mask lookup. Both actual helper inputs are explicit.
// Reference algorithm: src/hand/func_00215D00.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Mask { unsigned int words[4]; };
struct S { char prefix[0x2F4];struct Mask mask; };
void *func_00255130(void *receiver,const struct Mask *mask);
void *func_002553D8(struct S *p){struct Mask mask=p->mask;return func_00255130(p,&mask);}
