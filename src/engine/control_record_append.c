// SLY3_CFLAGS: -Os -G0
struct ControlRecordPrefix { int kind; unsigned int payload_word; };
extern unsigned char D_00479D2C[];
void *func_0011E118(void *pool);
void func_0011AD80(void *list,void *record);
void *func_00197628(void *owner,int kind,unsigned int payload_word)
{
    struct ControlRecordPrefix *record=func_0011E118(D_00479D2C);
    record->kind=kind;
    record->payload_word=payload_word;
    func_0011AD80((char *)owner+0x40,record);
    return record;
}
