// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int AssetSnapshotWord __attribute__((mode(TI)));
struct AssetSnapshotVirtual { short delta, pad; AssetSnapshotWord *(*matrix)(void *); };
struct AssetSnapshotObject { char prefix[0xC]; AssetSnapshotVirtual *table; };
struct AssetSnapshotRecord { int first, uid; AssetSnapshotObject *object; };
struct AssetSnapshotCache {
    char prefix[0xD8]; int count; char gapDC[8]; AssetSnapshotWord *points;
};
struct AssetSnapshotOwner {
    char prefix[0x44]; int count; AssetSnapshotRecord *records;
    AssetSnapshotCache *cache;
};
extern "C" {
extern char D_00475480[];
void func_001C7DC8(void *receiver);
AssetSnapshotCache *func_00231138(int uid, int count);
AssetSnapshotObject *func_0017E1B8(void *game, int policy, int uid, void *owner);
void func_0022DB08(void *cache);
}
extern "C" void func_0015E270(void *receiver)
{
    AssetSnapshotOwner *owner = static_cast<AssetSnapshotOwner *>(receiver);
    int i;
    func_001C7DC8(owner);
    owner->cache = func_00231138(0x6FC, owner->count);
    owner->cache->count = owner->count;
    for (i = 0; i < owner->count; i++) {
        AssetSnapshotRecord *record = &owner->records[i];
        AssetSnapshotObject *object = func_0017E1B8(
            D_00475480, 4, record->uid, owner);
        record->object = object;
        if (object) {
            AssetSnapshotWord *point = (AssetSnapshotWord *)(i * 16 + (int)owner->cache->points);
            *point = object->table[36].matrix(
                (char *)object + object->table[36].delta)[3];
        }
    }
    func_0022DB08(owner->cache);
}
