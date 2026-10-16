// SLY3_CFLAGS: -Os -G0
struct EngineCtorObject;
struct EngineCtorObject *func_00169C90(struct EngineCtorObject *receiver,void *owner,int order);
extern unsigned char D_00351570[];
struct EngineCtorRecord { void *owner; int order,kind; char unaccessedC[0x1C-0xC]; void *table; int argument; };
struct EngineCtorRecord *func_00130CD0(struct EngineCtorRecord *record,void *owner,int order,int argument)
{
    func_00169C90((struct EngineCtorObject *)record,owner,order);
    record->kind=5;
    record->table=D_00351570;
    record->argument=argument;
    return record;
}
