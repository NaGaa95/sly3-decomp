// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "heap.h"

struct ResourceChunkEntry40 {
    int id;
    unsigned char mode;
    unsigned char opaque5;
    signed char id_count;
    signed char key_count;
    unsigned char opaque8[8];
    unsigned int bytes;
    void *data;
    unsigned int qwords;
    unsigned char opaque1C[12];
};
typedef char ResourceChunkEntrySize40[(sizeof(ResourceChunkEntry40)==40)?1:-1];
extern "C" void func_00118DA0(void *stream,int bytes,void *output);
extern "C" void func_00118DF0(void *stream,int bytes);
extern "C" int func_00151C98(int count,const short *ids);
extern "C" int func_00151D10(int count,const int *keys);
extern "C" void *func_00236C18(int key);

extern "C" void func_00234648(void *stream,HEAP *heap,ResourceChunkEntry40 *entry)
{
    short ids[128];
    int keys[128];
    func_00118DA0(stream,24,entry);
    func_00118DA0(stream,entry->id_count*2,ids);
    func_00118DA0(stream,entry->key_count*4,keys);
    if(!func_00151C98(entry->id_count,ids) ||
       !func_00151D10(entry->key_count,keys)) {
        if(entry->mode!=1) {
            func_00118DF0(stream,entry->bytes);
            entry->data=0;
        }
        entry->mode=0;
        return;
    }
    if(entry->mode!=1) {
        ResourceChunkEntry40 *cached=(ResourceChunkEntry40 *)func_00236C18(entry->id);
        if(cached) {
            entry->data=cached->data;
            func_00118DF0(stream,entry->bytes);
        } else {
            entry->data=heap->PvAlloc(entry->bytes,0x2F);
            func_00118DA0(stream,entry->bytes,entry->data);
        }
    }
    entry->qwords=(entry->bytes+15)>>4;
}
