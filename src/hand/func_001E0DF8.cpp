// Preserve the original nullable attached-object query and signed-selector default/field result.
// Complete original input, boundary, relocation and whole initialized-section evidence are independently reviewed.
// Preserve the original blocked query and conditional default/field result.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" int func_00173428(void *);
extern "C" int func_001E0DF8(char *p) {
    bool blocked = false;
    void *object = *(void **)(p + 0x1108);
    if (object) blocked = func_00173428(object) != 0;
    if (blocked) return 0;
    return (!*(int *)(p+0x18DC) && *(int *)(p+0x1890)==-1) ? 1 : *(int *)(p+0x18A0);
}
