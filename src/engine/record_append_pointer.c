// SLY3_CFLAGS: -Os -G0
struct EngineRecordMethod { short delta,padding; void (*changed)(void *); };
struct EngineRecordPointer { void *value; int status; };
struct EngineRecord {
    char prefix[0x18];
    int pointer_count;
    struct EngineRecordPointer pointers[8];
    int id_count;
    int ids[4];
    char tail[0x7C];
    struct EngineRecordMethod *methods;
};
void func_0015C260(struct EngineRecord *record,void *value)
{
    if(record->pointer_count>=0 && record->pointer_count<8) {
        struct EngineRecordPointer *slot=&record->pointers[record->pointer_count];
        slot->value=value;
        slot->status=0;
        record->pointer_count++;
        record->methods[6].changed((char *)record+record->methods[6].delta);
    }
}
