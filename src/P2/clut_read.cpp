// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "heap.h"
struct ClutPixel { unsigned char red,green,blue,alpha; };
struct ClutReadCountBits {
    unsigned long reserved0:7;
    unsigned short color_count:9;
    unsigned long reserved16:48;
};
union ClutReadMetadata {
    struct ClutReadCountBits bits;
    struct { unsigned short flags,reservedA; ClutPixel *data; } pointer;
};
struct ClutReadEntry32 {
    int id;
    unsigned char mode,opaque5;
    signed char id_count,key_count;
    union ClutReadMetadata metadata;
    unsigned int quadword_count;
    unsigned char opaque14[12];
};
struct CachedClutData { unsigned char opaque0[12]; ClutPixel *data; };
typedef char ClutReadHeaderSize8[(sizeof(ClutReadCountBits)==8)?1:-1];
typedef char ClutReadMetadataSize8[(sizeof(ClutReadMetadata)==8)?1:-1];
typedef char ClutReadEntrySize32[(sizeof(ClutReadEntry32)==32)?1:-1];
typedef char ClutPixelSize4[(sizeof(ClutPixel)==4)?1:-1];
extern "C" {
    void func_00118DA0(void *stream,int bytes,void *output);
    void func_00118DF0(void *stream,int bytes);
    int func_00151C98(int count,const short *ids);
    int func_00151D10(int count,const int *keys);
    void *func_00236CF0(int id);
    void func_002338B8(ClutPixel *color);
    void func_00236908(ClutPixel *color);
}
extern "C" void func_00233EA8(void *stream,HEAP *heap,ClutReadEntry32 *entry)
{
    short ids[128];
    int keys[128];
    unsigned int bytes;
    func_00118DA0(stream,16,entry);
    bytes=entry->metadata.bits.color_count*sizeof(ClutPixel);
    func_00118DA0(stream,entry->id_count*2,ids);
    func_00118DA0(stream,entry->key_count*4,keys);
    if(!func_00151C98(entry->id_count,ids) ||
       !func_00151D10(entry->key_count,keys)) {
        if(entry->mode!=1)func_00118DF0(stream,bytes);
        entry->mode=0;
        return;
    }
    if(entry->mode!=1) {
        CachedClutData *cached=(CachedClutData *)func_00236CF0(entry->id);
        if(cached) {
            entry->metadata.pointer.data=cached->data;
            func_00118DF0(stream,bytes);
        } else {
            entry->metadata.pointer.data=(ClutPixel *)heap->PvAlloc(bytes,0x2F);
            func_00118DA0(stream,bytes,entry->metadata.pointer.data);
            if(entry->metadata.pointer.flags&1) {
                ClutPixel *color;
                for(color=entry->metadata.pointer.data;
                    (unsigned int)color < (unsigned int)entry->metadata.pointer.data+
                        entry->metadata.bits.color_count*sizeof(ClutPixel);++color)
                    func_002338B8(color);
            }
            {
                ClutPixel *color;
                for(color=entry->metadata.pointer.data;
                    (unsigned int)color < (unsigned int)entry->metadata.pointer.data+
                        entry->metadata.bits.color_count*sizeof(ClutPixel);++color)
                    func_00236908(color);
            }
        }
    }
    entry->quadword_count=(bytes+15)>>4;
}
