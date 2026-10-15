// Copy the complete sixteen-byte mask and test the explicit incoming index.253190 forwards unchanged incoming A1 to252AD0, which consumes it; this transitive input is expressed rather than relying on a live register.
// Reference algorithm: src/hand/func_001DD8E0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Mask { unsigned int words[4]; };
struct S { char prefix[0x2F4];struct Mask mask; };
int func_00253190(const struct Mask *mask,int index);
int func_002533C0(struct S *p,int index){struct Mask mask=p->mask;return func_00253190(&mask,index);}
