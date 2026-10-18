// SLY3_CFLAGS: -Os -G0
struct SaveSelectionView {
    unsigned char opaque00[0x13950];
    void *selectedBlock;
};
extern unsigned int D_004797C8;
extern unsigned char D_00375290[];
void func_00184968(void *self);
void func_0018AC60(void);
void func_00184A08(void *self)
{
    unsigned int flags = D_004797C8;
    if(flags & 1) {
        func_00184968(self);
        ((struct SaveSelectionView *)D_00375290)->selectedBlock = 0;
    } else if(flags & 0x10) func_0018AC60();
}
