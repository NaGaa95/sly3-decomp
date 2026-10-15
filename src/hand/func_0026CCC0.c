// Apply the inherited update and add both requested deltas through the original getter/setter APIs.
// Reference algorithm: src/hand/func_00144268.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001F48A0(void *p, int a, int b);
int func_001F43C8(void *p);
void func_001F43D0(void *p, int a);
int func_001F4430(void *p);
void func_001F4438(void *p, int a);
void func_0026CCC0(char *p, int a, int b)
{
    func_001F48A0(p, a, b);
    func_001F43D0(p, func_001F43C8(p) + a);
    func_001F4438(p, func_001F4430(p) + b);
}
