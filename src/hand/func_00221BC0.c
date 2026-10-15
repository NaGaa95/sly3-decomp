// Publish the actual stored selection, update its global selection helper, and issue the original five-input event descriptor.1C268 consumes integer A0;289070 saves all five inputs.
// Reference algorithm: src/hand/func_00152100.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S {char prefix[8];int selection;};
extern int D_003493A0;
extern char D_00475480[];
void func_0011C268(int selection);
void func_00289070(void *context,void *record,int id,int option,int selection);
void func_00221BC0(struct S *p){D_003493A0=p->selection;func_0011C268(p->selection);func_00289070(D_00475480,0,0x1A8,2,-1);}
