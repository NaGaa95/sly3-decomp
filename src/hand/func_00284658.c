// Apply the original global selection update when the stored record and global states request it.
// Reference algorithm: src/hand/func_0019CCE8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0x50];int state; };
struct S { char unknown_0[0x14]; struct R * record; };
struct G { char prefix[0x7CD4];int state; };
extern struct G D_004BC230;
void func_00284DC8(struct G *global,int selection);
void func_00284658(struct S *p){int state=p->record?p->record->state:-1;if(state==0 && D_004BC230.state==1)func_00284DC8(&D_004BC230,3);}
