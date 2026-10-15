// Find the explicit key in the owner record array and return its value, or zero when absent.
// Reference algorithm: src/hand/X509v3_data_type_by_NID.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct X { int key; int value; };
struct X *func_0026A108(void *owner, int key);
int func_0026A0E0(void *owner, int key)
{
    struct X *record = func_0026A108(owner, key);
    if (record == 0) return 0;
    else return record->value;
}
