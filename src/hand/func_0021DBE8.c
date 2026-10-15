// Reset both original global record groups and flush both original global allocation arrays with explicit record pointers; this initializer consumes no incoming argument.
// Reference algorithm: src/hand/func_002288D8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0046F7A0[],D_0046F810[],D_0036C2E0[],D_0036C308[];
void func_0021DD28(void *record);
void func_001746A8(void *record);
void func_0021DBE8(void){func_0021DD28(D_0046F7A0);func_0021DD28(D_0046F810);func_001746A8(D_0036C2E0);func_001746A8(D_0036C308);}
