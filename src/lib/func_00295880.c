// Reference: Sly 2 src/lib/func_00236C00.c; target Sly 3 0x00295880.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
void func_002999F0(void);
extern int _rpc_inited;
void func_00295880(void)
{
    func_002999F0();
    _rpc_inited = 0;
}
