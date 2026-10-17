// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
extern Qword D_00317570;
void func_0023AE08(void *receiver);
struct InitRecord { unsigned char prefix[0x3C]; unsigned int tagged; unsigned char gap40[0x144-0x40]; int word144; unsigned char gap148[0x150-0x148]; Qword vector; unsigned char gap160[0x164-0x160]; int word164; };

void func_0014D388(struct InitRecord *record)
{
    unsigned int value;
    func_0023AE08(record);
    record->word144 = -1;
    record->vector = D_00317570;
    record->word164 = -1;
    value = record->tagged;
    if((value ^ 1) & 1) *(unsigned int *)value |= 2;
    else record->tagged = value | 2;
}
