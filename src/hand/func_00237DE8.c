// Apply the original two-input record update and copy all four actual scalar controls from explicit input offsetsC..18 to receiver50..5C.
// Reference algorithm: src/hand/func_00144338.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0xC];float first,second,third,fourth;};
struct S { char unknown_0[0x50]; float first; float second; float third; float fourth; };
void func_00236FE0(void *receiver,const struct Record *record);
void func_00237DE8(struct S *p,const struct Record *record){func_00236FE0(p,record);p->first=record->first;p->second=record->second;p->third=record->third;p->fourth=record->fourth;}
