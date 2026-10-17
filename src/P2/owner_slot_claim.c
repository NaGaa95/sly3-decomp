// SLY3_CFLAGS: -Os -G0
struct Record { unsigned char bytes[0x80]; };
struct RecordPool { unsigned char prefix[0x44]; int count; unsigned char gap48[0x18]; struct Record records[17]; unsigned char gap8E0[0x58]; void *owners[17]; };
struct Record *func_0028A7D0(struct RecordPool *pool,void *owner)
{
    int i;
    for(i=0;i<pool->count;i++) {
        if(!pool->owners[i]) {
            pool->owners[i]=owner;
            return &pool->records[i];
        }
    }
    return 0;
}
