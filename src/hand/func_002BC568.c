// Clear the record header, mark its selection absent, and clear the byte flags.
// Reference algorithm: src/hand/func_001B34D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char header[8]; int selection; unsigned char flags; };
void *func_00292034(void *record,int value,int size);
void func_002BC568(struct R *record)
{
    func_00292034(record,0,sizeof(record->header));
    record->selection=-1;
    record->flags=0;
}
