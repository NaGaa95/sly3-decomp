/* Original module04 libsd export29. API evidence: pinned PS2SDK
 * common/include/libsd-common.h and libsd.h, archived privately.
 * The original setter stores its real void* input in this field.
 * No assembler adapter, register binding, or copied instructions. */
typedef char pointer_is_4[(sizeof(void*)==4)?1:-1];
extern void *Spu2IntrData;
void *sceSdGetSpu2IntrHandlerArgument(void)
{
    return Spu2IntrData;
}
