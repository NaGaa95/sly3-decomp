// Store the value returned by the original global-resource getter; its explicit context formal is provisional from callers.
// Reference algorithm: src/hand/func_00184208.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[];
struct S { char prefix[0x120]; int value; };
int func_001852E0(void *context);
void func_0026A1C8(struct S *object)
{
    object->value = func_001852E0(D_0036C700);
}
