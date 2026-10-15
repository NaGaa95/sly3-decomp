// Initialize the receiver and both embedded references, resolve the selected record and save its returned pointer. Complete152488->24D9D8->1F3BF8->23C580->1C7DC8->1C7F18 reads only incoming receiver before internal argument setup; other calls express all actual inputs.
// Reference algorithm: src/hand/func_00148BB0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x1190]; void * resource; };
void func_00152488(void *receiver);
void func_00258958(void *record);
void func_00155190(void *receiver,int id);
void *func_0023DDA0(void *receiver,int id,int kind);
void func_0022C2B0(struct S *p){func_00152488(p);func_00258958((char *)p+0x1480);func_00258958((char *)p+0x1530);func_00155190(p,0x2E);p->resource=func_0023DDA0(p,0x22,1);}
