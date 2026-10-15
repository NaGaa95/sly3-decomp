// Return the original object pointer consumed by the wrapper and actor callers.
// The concrete dynamic class is provisional; no returned address is treated as an integer.
// The actual pointer at receiver+0x110C is consumed through the original wrapper.
// Its concrete dynamic class remains provisional.
struct Fields { char prefix[0x110C]; void *result; };
void *func_001F4B30(void *receiver)
{
    return ((const struct Fields *)receiver)->result;
}
