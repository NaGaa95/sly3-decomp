// Apply the inherited owner update to the explicit receiver and initialize its two float controls.
// Reference algorithm: src/hand/func_00127D78.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x94]; float first; float second; };
void func_0023E110(void *owner,struct S *p);
void func_0027C238(void *owner,struct S *p){func_0023E110(owner,p);p->first=0.5f;p->second=0.1f;}
