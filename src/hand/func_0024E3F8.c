// Contribute one integer record count through the original receiver-only virtual slot.
// Complete original inputs, boundaries and initialized sections are independently reviewed.
// SLY3_CFLAGS: -Os -G0
// Original concrete slot67 contributes one record to the caller's integer count.
// The original method receives a caller-derived receiver but does not inspect it.
int func_0024E3F8(void *receiver) {
    (void)receiver;
    return 1;
}
