// Reference algorithm: src/hand/func_00208BB0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
// Actual caller-consumed pointer from controller[index].field110C.
struct Context  {
    char bytes[0x11C0];
};
extern struct Context D_0036E740[];
void *func_001F4B30(void *controller);
void *func_001F4AD0(void *unused,int index)  {
    return func_001F4B30(D_0036E740 + index);
}
