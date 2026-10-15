// Perform receiver cleanup and list insertion, add the receiver to its optional registration, and restore the original float time constant. Every consumed direct input is explicit.
// Reference algorithm: src/hand/func_001ABCE8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x3D8]; void * registration; char unknown_3DC[0xD7C]; float time; };
extern char D_00479B5C[];
extern float D_003273F8;
void func_0023CEC0(void *receiver);
void func_0011AF60(void *list,void *receiver);
void func_00256410(void *registration,void *receiver);
void func_00252A78(struct S *p){func_0023CEC0(p);func_0011AF60(D_00479B5C,p);if(p->registration)func_00256410(p->registration,p);p->time=D_003273F8;}
