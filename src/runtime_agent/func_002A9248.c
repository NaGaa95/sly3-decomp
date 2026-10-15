// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64
// Original cached ROMVER byte-array interface; only observed fields are read.
extern signed char D_0034DFB8[14];
extern signed char *func_002A91D8(void);
int func_002A9248(void)
{
    signed char *rom_version=D_0034DFB8;
    if(!rom_version[0]) func_002A91D8();
    return rom_version[4]=='T';
}
