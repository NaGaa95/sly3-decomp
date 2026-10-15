// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -Os -G0
// SLY3_ASFIX: sdk-gp64
// Actual cached ROMVER bytes and file-handle interfaces, recovered from original calls.
extern signed char D_0034DFB8[14];
extern const char D_0032C428[];
extern int func_00296B28(const char *path,int flags,...);
extern int func_00296F38(int descriptor,void *buffer,int count);
extern int func_00296DB8(int descriptor);
signed char *func_002A91D8(void)
{
    if(!D_0034DFB8[0]) {
        int descriptor=func_00296B28(D_0032C428,1);
        if(descriptor>=0) {
            func_00296F38(descriptor,D_0034DFB8,14);
            func_00296DB8(descriptor);
        }
    }
    return D_0034DFB8;
}
