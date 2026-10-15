// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Private repair: preserve actual receiver into the pointer equality query.
int func_00188A20(void *receiver);
void func_00188928(void *receiver);
void func_00188620(void *receiver) {
    if(func_00188A20(receiver))func_00188928(receiver);
}
