// Ensure the original six-word storage exists and store the explicit indexed value. Complete257F50 consumes receiver only, initializing its own allocation request and all six sentinel words; outer A1/A2 are saved data, not hidden helper inputs.
// Reference compiler shape: src/hand/func_001E08C0.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x17C4]; int * values; };
void func_00257F50(void *receiver);
void func_00257FC0(struct S *p,int index,int value){func_00257F50(p);p->values[index]=value;}
