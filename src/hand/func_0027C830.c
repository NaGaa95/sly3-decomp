// Store incoming F12 and the explicit eight-byte A2 record in the indexed96-byte embedded element; integer index A1 and receiver A0 remain explicit under the EE separate float register bank.
// Reference algorithm: src/hand/func_00163430.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Pair { unsigned int words[2]; };
struct Record { char prefix[0x14];float value;struct Pair pair;char suffix[0x60-0x20]; };
struct S { char prefix[0x190];struct Record records[0]; };
void func_0027C830(float value,struct S *p,int index,const struct Pair *pair){struct Record *record=p->records+index;record->value=value;record->pair=*pair;}
