// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
struct KEY;
struct Entry { int first; int second; int key; };
struct Table { unsigned char prefix[0x4FA8]; int count; struct Entry *entries; };
extern unsigned char D_00468D30[];
CRef *func_002BC010(CRef *output, struct KEY *key, unsigned char *buffer);
int func_0025EBC0(struct Table *table, int first, int second, int other)
{
    int index;
    if(first<other)
        return 1;
    if(other<first)
        return 0;
    for(index=0;index<table->count;index++) {
        struct Entry *entry=&table->entries[index];
        if(entry->first==first && entry->second==second) {
            CRef value;
            int result;
            func_002BC010(&value,(struct KEY *)entry->key,D_00468D30);
            result=value.payload.integer;
            func_0012BC20(&value);
            return result>=2;
        }
    }
    return 0;
}
