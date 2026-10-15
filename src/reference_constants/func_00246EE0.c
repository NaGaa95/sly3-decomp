// SLY3_CFLAGS: -Os -G0
// Index into the original four-byte entry storage. The original SUBU wraps its
// address-word difference modulo 2^32 before the signed arithmetic shift.
typedef unsigned int ADDRESS_WORD;
typedef struct ENTRY_STORAGE_VIEW {
    char prefix[0xFC];
    const void *base;
}
ENTRY_STORAGE_VIEW;
typedef char AddressWordIsFour[(sizeof(ADDRESS_WORD)==4)?1:-1];
int func_00246EE0(void *context,const void *entry) {
    ADDRESS_WORD difference=(ADDRESS_WORD)entry-(ADDRESS_WORD)((ENTRY_STORAGE_VIEW *)context)->base;
    return ((int)difference)>>2;
}
