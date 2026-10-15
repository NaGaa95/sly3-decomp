// Evaluate the object value and apply the returned float explicitly to the same receiver.
// Reference algorithm: src/hand/func_00174920.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
float func_0022DE50(void *p);
void func_0022F380(void *p, float value);
void func_0022F350(void *p)
{
    func_0022F380(p, func_0022DE50(p));
}
