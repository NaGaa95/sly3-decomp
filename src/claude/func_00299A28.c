// Sly 2 counterpart: sceSifAddCmdHandler (decomp src/hand/sceSifAddCmdHandler.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY3_ASM: gnu-reorder
typedef struct { void *func; void *data; void *gp; } SifCmdHandlerData;
typedef struct {
    int x0, x4, x8;
    SifCmdHandlerData *sys_cmd_buffer;
    int sys_size;
    SifCmdHandlerData *usr_cmd_buffer;
    int usr_size;
} SifCmdData;
extern SifCmdData D_004CF758;

static inline void *GetGp(void)
{
    void *gp;
    __asm__ volatile("move %0, $gp" : "=r"(gp) : : "memory");
    return gp;
}

void func_00299A28(int cid, void *handler, void *data)
{
    if (cid < 0) {
        D_004CF758.sys_cmd_buffer[cid & 0x7FFFFFFF].func = handler;
        D_004CF758.sys_cmd_buffer[cid & 0x7FFFFFFF].data = data;
        D_004CF758.sys_cmd_buffer[cid & 0x7FFFFFFF].gp = GetGp();
    } else {
        D_004CF758.usr_cmd_buffer[cid].func = handler;
        D_004CF758.usr_cmd_buffer[cid].data = data;
        D_004CF758.usr_cmd_buffer[cid].gp = GetGp();
    }
}
