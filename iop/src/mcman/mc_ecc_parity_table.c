/* PS2 memory-card ECC column parity for every unsigned input byte.
 * Each input bit chooses one member of each column-address parity pair.
 * The 0x80 bit records overall input parity; row parity is added by the kernel.
 * The original table is mutable initialized data, despite the current SDK const.
 */
#define ECC_PARITY_OF_BIT(index) \
    (0x80u | (((index) & 1u) ? 0x10u : 0x01u) | \
             (((index) & 2u) ? 0x20u : 0x02u) | \
             (((index) & 4u) ? 0x40u : 0x04u))

#define ECC_PARITY_OF_BYTE(value) \
    ((((value) & 0x01u) ? ECC_PARITY_OF_BIT(0) : 0u) ^ \
     (((value) & 0x02u) ? ECC_PARITY_OF_BIT(1) : 0u) ^ \
     (((value) & 0x04u) ? ECC_PARITY_OF_BIT(2) : 0u) ^ \
     (((value) & 0x08u) ? ECC_PARITY_OF_BIT(3) : 0u) ^ \
     (((value) & 0x10u) ? ECC_PARITY_OF_BIT(4) : 0u) ^ \
     (((value) & 0x20u) ? ECC_PARITY_OF_BIT(5) : 0u) ^ \
     (((value) & 0x40u) ? ECC_PARITY_OF_BIT(6) : 0u) ^ \
     (((value) & 0x80u) ? ECC_PARITY_OF_BIT(7) : 0u))

#define ECC_PARITY_ROW(start) \
    ECC_PARITY_OF_BYTE((start) + 0u), ECC_PARITY_OF_BYTE((start) + 1u), \
    ECC_PARITY_OF_BYTE((start) + 2u), ECC_PARITY_OF_BYTE((start) + 3u), \
    ECC_PARITY_OF_BYTE((start) + 4u), ECC_PARITY_OF_BYTE((start) + 5u), \
    ECC_PARITY_OF_BYTE((start) + 6u), ECC_PARITY_OF_BYTE((start) + 7u), \
    ECC_PARITY_OF_BYTE((start) + 8u), ECC_PARITY_OF_BYTE((start) + 9u), \
    ECC_PARITY_OF_BYTE((start) + 10u), ECC_PARITY_OF_BYTE((start) + 11u), \
    ECC_PARITY_OF_BYTE((start) + 12u), ECC_PARITY_OF_BYTE((start) + 13u), \
    ECC_PARITY_OF_BYTE((start) + 14u), ECC_PARITY_OF_BYTE((start) + 15u)

unsigned char mcman_xor_table[256] = {
    ECC_PARITY_ROW(0x00u), ECC_PARITY_ROW(0x10u),
    ECC_PARITY_ROW(0x20u), ECC_PARITY_ROW(0x30u),
    ECC_PARITY_ROW(0x40u), ECC_PARITY_ROW(0x50u),
    ECC_PARITY_ROW(0x60u), ECC_PARITY_ROW(0x70u),
    ECC_PARITY_ROW(0x80u), ECC_PARITY_ROW(0x90u),
    ECC_PARITY_ROW(0xA0u), ECC_PARITY_ROW(0xB0u),
    ECC_PARITY_ROW(0xC0u), ECC_PARITY_ROW(0xD0u),
    ECC_PARITY_ROW(0xE0u), ECC_PARITY_ROW(0xF0u)
};
