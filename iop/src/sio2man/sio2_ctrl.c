/* Sly 3 USA IOP source recovery: module_00.irx, sio2man exports 4 and 5.
 * API provenance: pinned official PS2SDK sio2man.h, archived alongside its
 * Academic Free License 2.0 notice. These two implementations independently
 * express the original volatile 32-bit SIO2 control-register accesses.
 * A zero-frame leaf match does not confirm the original compiler or the
 * general O32 stack/call ABI. No main EE source or build profile uses this TU.
 */
typedef unsigned int u32;
typedef char iop_u32_must_be_32_bits[(sizeof(u32) == 4) ? 1 : -1];
typedef char iop_pointer_must_be_32_bits[(sizeof(void *) == 4) ? 1 : -1];

void sio2_ctrl_set(u32 value)
{
    *(volatile u32 *)0xBF808268u = value;
}

u32 sio2_ctrl_get(void)
{
    return *(volatile u32 *)0xBF808268u;
}
