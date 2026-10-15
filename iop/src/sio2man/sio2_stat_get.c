/* Sly 3 USA IOP scalar source recovery; historical compiler/general ABI unconfirmed. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef char iop_u32_4[(sizeof(u32)==4)?1:-1];
typedef char iop_pointer_4[(sizeof(void*)==4)?1:-1];
u32 sio2_stat_get(void)
{
    return *(volatile u32 *)0xBF808280u;
}
