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
void func_0015C4A8(struct EngineRecord *record,int id)
{
    if(record->id_count>=0 && record->id_count<4) {
        record->ids[record->id_count++]=id;
        record->methods[6].changed((char *)record+record->methods[6].delta);
    }
}
