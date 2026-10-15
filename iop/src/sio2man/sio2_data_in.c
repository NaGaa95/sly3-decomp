/* Sly 3 USA sio2man export20: byte FIFO read at 0xBF808264.
 * Primary public signature: ps2sdk sio2man.h at
 * 329e2bb43287e16af16c4dde1c614e2662c24468.
 * Historical IOP compiler and general calling ABI remain unconfirmed.
 */
typedef unsigned char u8;
typedef char iop_u8_1[(sizeof(u8)==1)?1:-1];
typedef char iop_pointer_4[(sizeof(void*)==4)?1:-1];

static inline volatile u8 *mmio_page(void)
{
    return (volatile u8 *)0xBF810000u;
}

u8 sio2_data_in(void)
{
    return mmio_page()[-0x7D9C];
}
